/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 01:47:00 by motoure           #+#    #+#             */
/*   Updated: 2021/09/21 01:14:28 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

char	*get_prompt_of(t_msh *msh, char *cwd)
{
	char		*ret;
	char		*arrow;
	char		*home_path;
	t_cut_cmd	*home;

	(void)arrow;
	home_path = NULL;
	home = get_env_of(msh->envp, "HOME");
	if (!home)
		return ("msh$ ");
	if (home)
		home_path = ft_split(home->elem, '=')[1];
	if (home && is_same(home_path, cwd))
		cwd = ft_strdup("/~");
	if (!cwd)
		cwd = get_val_from_var(get_env_of(msh->tools->tail, "PWD"));
	cwd = ft_strrev(cwd);
	if (is_same(cwd, "/"))
		ret = ft_strndup("/", 1);
	else
		ret = ft_strndup(cwd, get_c_index(cwd, '/'));
	if (ft_strlen(cwd) < ft_strlen(home_path)
		&& !is_same(ret, "/") && !is_same(ret, "~"))
		ret = ft_strjoin(ret, "/");
	return (ft_strjoin(ft_strrev(ret), " "));
}

static void	get_line_prompt(t_msh *msh, char *str)
{
	char	*curr_path;

	if (str)
		curr_path = str;
	else
		curr_path = get_prompt_of(msh, get_cwd());
	if (msh->tools->status != 0)
		msh->jobs->reading_line = to_gc((void ***)
				readline(ft_strjoin(" ✗ ", curr_path)));
	else
		msh->jobs->reading_line = to_gc((void ***)
				readline(ft_strjoin(" ➜ ", curr_path)));
	if (!msh->jobs->reading_line)
	{
		flag("push CTRLD=true");
		handler(0);
	}
}

int	get_line(t_msh *msh, char *str)
{
	(void)str;
	get_line_prompt(msh, str);
	if (is_same(ft_strtrim(msh->jobs->reading_line, "\n"), "")
		|| is_same(ft_strtrim(msh->jobs->reading_line, " "), ""))
	{
		msh->tools->status = 0;
		msh->jobs->reading_line = NULL;
		return (0);
	}
	else
	{
		msh->jobs->have_been_read = ft_strdup(msh->jobs->reading_line);
		if (flag("HEREDOC != true"))
		{
			add_history(msh->jobs->reading_line);
			ft_putstr_fd(ft_strjoin(msh->jobs->reading_line, "\n"),
				msh->tools->history_fd);
		}
	}
	return (1);
}
