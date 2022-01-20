/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:57:09 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 20:57:11 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libshell.h"

void	get_history_from_fd(int fd)
{
	char	buff[2];
	char	*ret;

	ret = NULL;
	while (read(fd, &buff, 1))
	{
		buff[1] = '\0';
		if (!ret)
			ret = ft_strdup(buff);
		else
			ret = ft_strjoin(ret, buff);
		if (buff[0] == '\n')
		{
			add_history(ret);
			ret = NULL;
		}
	}
	if (ret)
		add_history(ret);
}

int	init_history(t_msh *msh)
{
	t_cut_cmd	*home;

	(void)msh;
	home = get_env_of(msh->envp, "HOME");
	if (!home || split_len(ft_split(home->elem, '=')) != 2)
	{
		ft_putstr_fd(ft_strjoin(ft_strjoin(
					"minishell: failed to get home path!\n",
					"-> history won't be working for current session\n"),
				"-> dynamic prompt won't be working for current session\n"), 2);
		return (0);
	}
	msh->tools->history_fd = open(ft_strjoin(ft_split(home->elem, '=')[1],
				"/.history.msh"), O_CREAT | O_RDWR | O_APPEND, 0666);
	if (msh->tools->history_fd == -1)
	{
		ft_putstr_fd(ft_strjoin("minishell: failed to initialize history\n",
				"-> history won't be saved at session exit\n"), 2);
		return (0);
	}
	get_history_from_fd(msh->tools->history_fd);
	return (1);
}

int	init_shell(void)
{
	char	bp[1024];

	if (tgetent(bp, getenv("minishell")) != 1)
	{
		ft_putstr_fd("minishell: initalization failed, exiting now", 2);
		exit(255);
	}
	return (1);
}

void	_label_prompt(t_msh *msh)
{
	while (msh->tools->run_status)
	{
		get_line(msh, NULL);
		if (p_process_line(msh))
			_placeholder_handle_cmd(msh);
		write_error(msh);
		msh->jobs->have_been_read = NULL;
		msh->jobs->reading_line = NULL;
		msh->tools->head = NULL;
		msh->tools->tail = NULL;
		gc("collect");
	}
	gc("collect -all");
}

int	main(int argc, char **argv, char **envp)
{
	t_msh	*msh;

	(void)argc;
	(void)argv;
	signal(SIGINT, handler);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	init_shell();
	gc_init();
	gc("pause");
	init_msh(&msh, envp);
	init_history(msh);
	gc("resume");
	g_gc->msh_ptr = msh;
	g_gc->spawn_prompt = _label_prompt;
	g_gc->spawn_prompt(g_gc->msh_ptr);
	return (0);
}
