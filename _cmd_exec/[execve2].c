/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [execve2].c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 01:39:46 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/15 03:24:56 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

char	*get_val_from_var(t_cut_cmd *var)
{
	char	*try;

	if (var)
	{
		try = ft_strchr(var->elem, '=');
		if (try && *try == '=')
		{
			if (!(*try + 1))
				return (NULL);
			else
				return (ft_strdup(try + 1));
		}
	}
	return (NULL);
}

char	*_place_holder_get_path(t_msh *msh, t_cut_cmd *cmd)
{
	t_cut_cmd	*ls;
	int			i;
	char		*tmp2;

	i = 0;
	tmp2 = determine_path_type(cmd, ft_strdup(cmd->elem));
	msh->path = NULL;
	if (tmp2)
		msh->path = ft_split(tmp2, ' ');
	else if (get_env_of(msh->envp, "PATH"))
		msh->path = ft_split(get_val_from_var
				(get_env_of(msh->envp, "PATH")), ':');
	while (msh->path && msh->path[i])
	{
		ls = ft_ls(msh->path[i], NULL);
		while (ls)
		{
			if (is_same(ls->elem, cmd->elem))
				return (ft_strjoin(msh->path[i], ft_strjoin("/", cmd->elem)));
			ls = ls->n;
		}
		i++;
	}
	return (NULL);
}

void	delete_heredoc(t_msh *msh)
{
	t_cut_cmd	*to_delete;
	char		**delete_args;
	int			pid2;

	pid2 = fork();
	if (pid2 == 0)
	{
		to_delete = (t_cut_cmd *)gc_malloc(sizeof(t_cut_cmd));
		to_delete->elem = ft_strdup("/bin/rm");
		delete_args = ft_split("rm -rf ./.msh_heredoc.msh", ' ');
		msh->tools->marker = NULL;
		execve(to_delete->elem, delete_args, list_to_split(msh->env->head));
	}
	else
		waitpid(pid2, (void *)0, 0);
}

void	quotes_to_arg(t_cut_cmd *cmd)
{
	t_cut_cmd	*iterator;

	iterator = cmd;
	while (iterator)
	{
		if (iterator->__token__ == D_QUOTE || iterator->__token__ == S_QUOTE)
		{
			if (iterator->elem)
			{
				if (iterator->elem[0] == '\'')
					iterator->__token__ = OPTION;
				else
					iterator->__token__ = ARG;
			}
		}
		iterator = iterator->p;
	}
}

void	simple_exec(t_msh *msh, t_cut_cmd *cmd)
{
	int		pid;
	int		bfd;

	bfd = -1;
	pipe(msh->tools->pipe);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		son_fork(msh, cmd, bfd);
	else if (pid > 0)
		father_fork(msh, cmd, pid, &bfd);
	else
		append_error(msh, cmd, "PID NEGATIVE", 0);
}
