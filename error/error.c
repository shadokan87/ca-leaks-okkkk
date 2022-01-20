/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:55:19 by motoure           #+#    #+#             */
/*   Updated: 2021/09/21 01:09:03 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

int	add_to_error(t_msh *msh, char *elem, t_token __token__)
{
	t_cut_cmd	*ret;

	ret = fill(elem, __token__);
	if (!msh->tools->errors)
	{
		msh->tools->errors = ret;
		return (1);
	}
	ret->n = msh->tools->errors;
	msh->tools->errors = ret;
	return (1);
}

int	append_error(t_msh *msh, t_cut_cmd *cmd, char *msg, int ret)
{
	char	*str;

	(void)ret;
	(void)cmd;
	(void)msh;
	(void)cmd;
	(void)msg;
	msh->tools->status = ret;
	if (msh->tools->is_folder)
	{
		str = ft_strjoin("minishell: ", cmd->elem);
		msh->tools->error_msg = ft_strjoin(str, ": Is a directory");
		ft_putendl_fd(msh->tools->error_msg, 2);
		free(str);
	}
	if (msg)
		add_to_error(msh, msg, _UNASSIGNED);
	if (msh->tools->is_folder)
	{
		free(msh->tools->error_msg);
		exit (0);
	}
	return (ret);
}

void	command_not_found(t_msh *msh, char *str)
{
	char	*tmp;

	(void)str;
	(void)msh;
	msh->tools->to_p = ft_strjoin("minishell: ", str);
	tmp = ft_strjoin(msh->tools->to_p, ": command not found ");
	append_error(msh, NULL, tmp, errno);
}

void	write_error(t_msh *msh)
{
	(void)msh;
	if (msh->tools->error_msg)
	{
		write(2, msh->tools->error_msg, ft_strlen(msh->tools->error_msg));
		write(2, "\n", 1);
	}
	while (msh->tools->errors)
	{
		printf("%s\n", msh->tools->errors->elem);
		msh->tools->errors = msh->tools->errors->n;
	}
	msh->tools->error_msg = NULL;
	msh->tools->errors = NULL;
}

void	handler(int n)
{
	(void)n;
	if (flag("CTRLD == true"))
	{
		gc("collect -all");
		exit (0);
	}
	else
	{
		rl_on_new_line();
		write(0, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
