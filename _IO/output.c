/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:55:36 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/09 20:14:10 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

int	is_output(t_cut_cmd **cmd)
{
	while ((*(cmd)) && (*(cmd))->__token__ != PIPE)
	{
		if ((*cmd)->__token__ == OR || (*cmd)->__token__ == AND
			|| (*cmd)->__token__ == CLOSED_DIV || (*cmd)->__token__ == OPEN_DIV)
			break ;
		if ((*(cmd))->__token__ == R_REDIR || (*(cmd))->__token__ == D_R_REDIR)
			return (SUCCESS);
		(*(cmd)) = (*(cmd))->p;
	}
	return (ERROR);
}

static void	div_redir_cut(t_msh *msh, t_cut_cmd *cmd)
{
	if (flag("TRUNC_NEXT == true"))
		ft_open(&msh->tools->fdout,
			open(cmd->elem, O_RDWR | O_CREAT | O_TRUNC, 0666));
	ft_open(&msh->tools->fdout,
		open(cmd->elem, O_RDWR | O_CREAT | O_APPEND, 0666));
	if (msh->tools->fdout < 0)
		append_error(msh, cmd, NULL, errno);
}

int	div_output_redirection(t_msh *msh, t_cut_cmd *cmd)
{
	if (is_div_output(&cmd) == SUCCESS)
	{
		while ((cmd != NULL && cmd->__token__ != PIPE) && (cmd->__token__ == ARG
				|| cmd->__token__ == R_REDIR || cmd->__token__ == D_R_REDIR))
		{
			if (cmd->__token__ == ARG && cmd->n->__token__ == R_REDIR)
				div_redir_cut(msh, cmd);
			else if (cmd->__token__ == ARG && cmd->n->__token__ == D_R_REDIR)
			{
				ft_open(&msh->tools->fdout,
					open(cmd->elem, O_RDWR | O_CREAT | O_APPEND, 0666));
				if (msh->tools->fdout < 0)
					append_error(msh, cmd, NULL, errno);
			}
			cmd = cmd->p;
		}
		dup2(msh->tools->fdout, 1);
		flag("push TRUNC_NEXT=false");
		return (SUCCESS);
	}
	return (ERROR);
}

static void	redir_cut(t_msh *msh, t_cut_cmd *cmd)
{
	ft_open(&msh->tools->fdout,
		open(cmd->elem, O_RDWR | O_CREAT | O_TRUNC, 0666));
	if (msh->tools->fdout < 0 || is_folder(&msh, cmd->elem))
		append_error(msh, cmd, NULL, errno);
}

int	output_redirection(t_msh *msh, t_cut_cmd *cmd)
{
	if (node_match(msh->tools->flag_map, cmd))
		flag("push TRUNC_NEXT=true");
	if (is_output(&cmd) == SUCCESS)
	{
		while ((cmd != NULL && cmd->__token__ != PIPE) && (cmd->__token__ == ARG
				|| cmd->__token__ == R_REDIR || cmd->__token__ == D_R_REDIR))
		{
			if (cmd->__token__ == ARG && cmd->n->__token__ == R_REDIR)
				redir_cut(msh, cmd);
			else if (cmd->__token__ == ARG && cmd->n->__token__ == D_R_REDIR)
			{
				ft_open(&msh->tools->fdout,
					open(cmd->elem, O_RDWR | O_CREAT | O_APPEND, 0666));
				if (msh->tools->fdout < 0)
					append_error(msh, cmd, NULL, errno);
			}
			cmd = cmd->p;
		}
		dup2(msh->tools->fdout, 1);
		return (SUCCESS);
	}
	return (div_output_redirection(msh, cmd));
}
