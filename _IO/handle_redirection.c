/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:57:27 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 20:00:24 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

t_cut_cmd	*node_match(t_cut_cmd **target, t_cut_cmd *to_find)
{
	int	i;

	i = 0;
	while (target && target[i])
	{
		if (target[i] == to_find)
			return (target[i]);
		i++;
	}
	return (NULL);
}

int	is_div_output(t_cut_cmd **cmd)
{
	register int	deep;

	deep = 1;
	while ((*(cmd)) && (*(cmd))->__token__ != CLOSED_DIV)
		(*(cmd)) = (*(cmd))->p;
	if (*cmd)
	{
		while (deep)
		{
			(*(cmd)) = (*(cmd))->p;
			deep--;
		}
		if ((*cmd))
		{
			if ((*(cmd))->__token__ == R_REDIR
				|| (*(cmd))->__token__ == D_R_REDIR)
				return (SUCCESS);
		}
	}
	return (ERROR);
}

int	is_folder(t_msh **msh, char *str)
{
	DIR	*de;

	de = opendir(str);
	if (de)
	{
		(*msh)->tools->is_folder = 1;
		closedir(de);
		return (1);
	}
	return (0);
}

int	isredir(t_cut_cmd *cmd)
{
	while (cmd != NULL && cmd->__token__ != PIPE)
	{
		if (cmd->__token__ == OR || cmd->__token__ == AND)
			break ;
		if (cmd->__token__ == R_REDIR || cmd->__token__ == L_REDIR
			|| cmd->__token__ == D_R_REDIR)
			return (SUCCESS);
		cmd = cmd->p;
	}
	return (ERROR);
}

/*
** print_list_msg2(NULL, NULL);
*/
int	handle_redirection(t_msh *msh, t_cut_cmd *cmd, int fd)
{
	int	ret;

	ret = isredir(cmd);
	if ((ret == -1) && (fd >= 0))
	{
		if (!cmd->is_last)
			dup2(msh->tools->pipe[1], 1);
		return (SUCCESS);
	}
	else
	{
		ft_open(&msh->tools->fdin, -1);
		ft_open(&msh->tools->fdout, -1);
		msh->tools->b_stdout = dup(STDOUT_FILENO);
		input_redirection(msh, cmd);
		output_redirection(msh, cmd);
	}
	return (SUCCESS);
}
