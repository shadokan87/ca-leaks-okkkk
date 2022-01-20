/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:55:27 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 00:26:53 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

int	is_input(t_cut_cmd **cmd)
{
	while ((*(cmd)) && (*(cmd))->__token__ != PIPE)
	{
		if ((*cmd)->__token__ == L_REDIR || (*cmd)->__token__ == D_L_REDIR)
			return (SUCCESS);
		(*(cmd)) = (*(cmd))->p;
	}
	return (ERROR);
}

char	*heredoc_env(t_msh *msh, char *str)
{
	head_tail(msh, "backup");
	add(msh, str, C_BUILTIN);
	_place_holder_handle_expand_env(msh, msh->tools->tail);
	str = ft_strdup(msh->tools->tail->elem);
	head_tail(msh, "restore");
	return (str);
}

static void	double_left(t_msh *msh, t_cut_cmd *cmd)
{
	flag("push HEREDOC=true");
	msh->tools->marker = cmd->elem;
	msh->tools->tmp_node = cmd;
	msh->tools->tmpfd = open("./.msh_heredoc.msh",
			O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (msh->tools->tmpfd < 0)
		append_error(msh, cmd, NULL, errno);
	while (get_line(msh, "> ") >= 0)
	{
		if (msh->jobs->have_been_read
			&& is_same(msh->jobs->have_been_read, msh->tools->marker))
			break ;
		if (msh->jobs->have_been_read)
			ft_putendl_fd(heredoc_env(msh, msh->jobs->have_been_read),
				msh->tools->tmpfd);
		else
			ft_putendl_fd("", msh->tools->tmpfd);
		msh->jobs->have_been_read = NULL;
	}
	msh->tools->istmp = 2;
	flag("push HEREDOC=false");
}

int	input_redirection(t_msh *msh, t_cut_cmd *cmd)
{
	if (is_input(&cmd) == SUCCESS)
	{
		while ((cmd && cmd->__token__ != PIPE) && (cmd->__token__ == ARG
				|| cmd->__token__ == L_REDIR || cmd->__token__ == D_L_REDIR))
		{
			if (cmd->__token__ == ARG && cmd->n->__token__ == L_REDIR)
			{
				msh->tools->fdin = open(cmd->elem, O_RDWR, NULL);
				if (msh->tools->fdin < 0)
					append_error(msh, cmd, NULL, errno);
				msh->tools->istmp = 0;
				dup2(msh->tools->fdin, 0);
			}
			else if (cmd->__token__ == ARG && cmd->n->__token__ == D_L_REDIR)
				double_left(msh, cmd);
			cmd = cmd->p;
		}
		return (SUCCESS);
	}
	return (ERROR);
}
