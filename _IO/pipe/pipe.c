/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 20:00:59 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/09 20:15:13 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libshell.h"

void	ispipe(t_msh *msh)
{
	t_cut_cmd	*cmd;
	int			cpt;

	cmd = msh->tools->tail;
	cpt = 0;
	while (cmd != NULL)
	{
		if (cmd->__token__ == PIPE)
			cpt++;
		cmd = cmd->p;
	}
	msh->tools->nbpipe = cpt;
}

int	getnext_pipe(t_cut_cmd **cmd)
{
	while ((*(cmd)) != NULL && (*(cmd))->__token__ != PIPE)
		(*(cmd)) = (*(cmd))->p;
	if ((*(cmd)) != NULL)
		(*(cmd)) = (*(cmd))->p;
	while ((*cmd) != NULL && (*cmd)->__token__ == OPEN_DIV)
		(*(cmd)) = (*(cmd))->p;
	if ((*(cmd)))
		return (SUCCESS);
	else
		return (-1);
}

void	whatpostions(t_msh *msh)
{
	t_cut_cmd	*cmd;
	t_cut_cmd	*tmp;

	cmd = msh->tools->tail;
	while (cmd != NULL)
	{
		tmp = cmd;
		if (getnext_pipe(&cmd) == -1)
			tmp->is_last = 1;
	}
}
