/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_type[pipe_no_pipe].c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 02:00:52 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/15 03:17:39 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

void	son_fork(t_msh *msh, t_cut_cmd *cmd, int bfd)
{
	char	*exec_path;
	char	**args;

	signal(SIGINT, SIG_DFL);
	if (bfd >= 0)
		dup2(bfd, 0);
	handle_redirection(msh, cmd, bfd);
	if (cmd && cmd->__token__ == C_BUILTIN)
		handle_builtins(msh, cmd);
	else
	{
		exec_path = _place_holder_get_path(msh, cmd);
		if (!exec_path && !is_builtin(cmd->elem))
			exit(127);
		args = handle_args(msh, cmd);
		execve(exec_path, args, list_to_split(msh->env->head));
		exit (errno);
	}
}

void	father_fork(t_msh *msh, t_cut_cmd *cmd, int pid, int *bfd)
{
	(void)cmd;
	waitpid(pid, &msh->tools->status, 0);
	signal(SIGINT, handler);
	signal(SIGTERM, SIG_IGN);
	set_exit_status(msh, cmd);
	if (*bfd > 0)
	{
		close(msh->tools->pipe[1]);
		*bfd = msh->tools->pipe[0];
	}
	if ((open("./.msh_heredoc.msh", O_RDONLY, 0666)) != -1)
		delete_heredoc(msh);
}

static void	new_fork(t_msh **msh, int pid)
{
	t_cut_cmd	*new;

	if ((*msh)->tools->w_pids->head == NULL)
	{
		gc("pause");
		new = (t_cut_cmd *)gc_malloc(sizeof(t_cut_cmd));
		gc("resume");
		new->pid = pid;
		new->n = NULL;
		new->p = NULL;
		(*msh)->tools->w_pids->head = new;
		(*msh)->tools->w_pids->tail = new;
	}
	else
	{
		gc("pause");
		new = (t_cut_cmd *)gc_malloc(sizeof(t_cut_cmd));
		gc("resume");
		new->pid = pid;
		new->n = NULL;
		new->p = (*msh)->tools->w_pids->tail;
		(*msh)->tools->w_pids->tail->n = new;
		(*msh)->tools->w_pids->tail = new;
		(*msh)->tools->w_pids->size++;
	}
}

static void	pipe_process(t_msh *msh, t_cut_cmd *cmd, int pid, int *bfd)
{
	pipe(msh->tools->pipe);
	if ((cmd->p && cmd->p->__token__ == C_BUILTIN)
		&& is_same(cmd->elem, "export"))
		builtin_export(msh, cmd);
	if ((cmd->p && cmd->p->__token__ == ARG)
		&& is_same(cmd->elem, "unset"))
		builtin_unset(msh, cmd);
	else if ((cmd->p && cmd->p->__token__ == ARG)
		&& is_same(cmd->elem, "cd"))
		builtin_cd(msh, cmd);
	else
	{
		pid = fork();
		new_fork(&msh, pid);
		if (pid == 0)
			son_fork(msh, cmd, *bfd);
		else if (pid > 0)
		{
			close(msh->tools->pipe[1]);
			*bfd = msh->tools->pipe[0];
		}
		else
			append_error(msh, cmd, "PID NEGATIVE", 0);
	}
}

void	cmd_pipe(t_msh *msh, t_cut_cmd *cmd)
{
	t_cut_cmd	*w_pids;
	t_cut_cmd	*tmp;
	int			pid;
	int			bfd;
	char		*str;

	bfd = 0;
	pid = 0;
	(void)str;
	while (cmd != NULL)
	{
		pipe_process(msh, cmd, pid, &bfd);
		getnext_pipe(&cmd);
	}
	w_pids = msh->tools->w_pids->head;
	while (w_pids)
	{
		waitpid(w_pids->pid, &msh->tools->status, 0);
		if ((open("./.msh_heredoc.msh", O_RDONLY, 0666)) != -1)
			delete_heredoc(msh);
		tmp = w_pids;
		w_pids = w_pids->n;
	}
}
