/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 02:53:06 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/11 19:16:36 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

/* BECAREFULL TO CHANGE THE MALLOC TO GC OR CALLOC ! */
void	init_jobs(t_msh **msh)
{
	(*msh)->jobs = (t_job *)gc_malloc(sizeof(t_job));
	if (!(*msh)->jobs)
		handler(0);
	(*msh)->jobs->reading_line = NULL;
	(*msh)->jobs->have_been_read = NULL;
	(*msh)->jobs->prompt_status = 0;
}

static	void	init_tools2(t_msh *msh)
{
	msh->tools->history_fd = -1;
	msh->tools->noforked_exit = 0;
	msh->tools->echo_opt = 0;
	msh->tools->error_msg = NULL;
	msh->tools->marker = NULL;
	msh->tools->to_p = NULL;
	msh->tools->errors = NULL;
	msh->tools->flag_map = NULL;
	msh->envp = NULL;
	flag("push INIT=INIT");
}

/*where is tmp node ? */
void	init_tools(t_msh *msh)
{
	msh->tools = gc_malloc(sizeof(t_tools));
	if (!msh->tools)
		handler(0);
	msh->tools->w_pids = (t_pid_list *)gc_malloc(sizeof(t_pid_list));
	msh->tools->tmp_node = 0;
	msh->tools->b_stdout = 0;
	msh->tools->head = NULL;
	msh->tools->tail = NULL;
	msh->tools->w_pids->tail = NULL;
	msh->tools->w_pids->head = NULL;
	msh->tools->fdin = 0;
	msh->tools->fdout = 1;
	msh->tools->tmpfd = 0;
	msh->tools->nbpipe = 0;
	msh->tools->nbredir = 0;
	msh->tools->istmp = 0;
	msh->tools->last_op = 0;
	msh->tools->status = 0;
	msh->tools->run_status = 1;
	msh->tools->tmp_status = 0;
	msh->tools->pipe[0] = 0;
	msh->tools->pipe[1] = 0;
	init_tools2(msh);
}

/* BECAREFULL TO CHANGE THE MALLOC TO GC OR CALLOC ! */
void	init_env(t_msh *msh, char **envp)
{
	int		i;

	i = 0;
	gc("pause");
	msh->env = (t_env_list *)gc_malloc(sizeof(t_env_list));
	msh->env->head = NULL;
	msh->env->tail = NULL;
	msh->env->sub = NULL;
	create_env_list(&msh, envp[i]);
	while (envp[++i])
		add_env(&msh, envp[i], 0);
	gc("resume");
}

/* BECAREFULL TO CHANGE THE MALLOC TO GC OR CALLOC ! */
void	init_msh(t_msh **msh, char **envp)
{
	t_cut_cmd	*ptr;

	*msh = (t_msh *)gc_malloc(sizeof(t_msh));
	init_jobs(msh);
	init_tools(*msh);
	init_env(*msh, envp);
	ptr = get_env_of((*msh)->env->head, "PATH");
	(*msh)->path = ft_split(ft_split(ptr->elem, '=')[1], ':');
	if (!(*msh)->path)
	{
		printf("PATH INIT FAILED\n");
		exit (0);
	}
	(*msh)->envp = (*msh)->env->head;
	if (!(*msh)->envp)
	{
		printf("ENVP INIT FAILED\n");
		exit (0);
	}
}
