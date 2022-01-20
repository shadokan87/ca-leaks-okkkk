/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 02:25:05 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 20:03:16 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

int	goto_next_div(t_msh *msh, t_cut_cmd **pos)
{
	(*pos) = (*pos)->p;
	if ((*pos) && (*pos)->__token__ == OR)
	{
		if ((*pos)->p && (*pos)->p->__token__ != OPEN_DIV && msh->tools->status)
		{
			(*pos) = (*pos)->p;
			return (1);
		}
		while ((*pos))
		{
			if ((*pos) && ((*pos)->__token__ == AND)
				&& ((*pos)->n->__token__ == CLOSED_DIV))
				break ;
			else if ((msh->tools->status)
				&& ((*pos) && (*pos)->n->__token__ == OPEN_DIV))
				break ;
			(*pos) = (*pos)->p;
		}
	}
	return (1);
}

t_cut_cmd	*get_next_token_scope(t_cut_cmd *pos, t_token __token__)
{
	t_cut_cmd	*iterator;

	iterator = pos;
	if (!pos)
		return (NULL);
	if (flag("SKZERO == true")
		&& iterator->__token__ == __token__)
		iterator = iterator->p;
	while (iterator)
	{
		if (((iterator->__token__ == AND && flag("SKAND != true"))
				|| (iterator->__token__ == OR && flag("SKOR != true"))
				|| (iterator->__token__ == CLOSED_DIV && flag("SKCDIV != true"))
				|| (iterator->__token__ == OPEN_DIV && flag("SKODIV != true"))))
			break ;
		if (iterator->__token__ == __token__)
			return (iterator);
		iterator = iterator->p;
	}
	return (NULL);
}

t_token	scope_contain_redir(t_cut_cmd *pos)
{
	t_token		try;
	t_cut_cmd	*get_next_token_try;

	try = R_REDIR;
	while (try <= D_L_REDIR)
	{
		get_next_token_try = get_next_token_scope(pos, try);
		if (get_next_token_try)
			return (try);
		try++;
	}
	return (_UNASSIGNED);
}

int	catch_and(t_msh *msh, t_cut_cmd **pos)
{
	register int	deep;

	deep = 0;
	if ((*pos)->__token__ != AND)
		return (0);
	if (((*pos)->n && (*pos)->n->__token__ == CLOSED_DIV)
		|| ((*pos)->p && (*pos)->p->__token__ == OPEN_DIV))
	{
		msh->tools->flag_map = NULL;
		flag_loop("NULL:push INIT=INIT");
	}
	if (!msh->tools->status)
	{
		(*pos) = (*pos)->p;
		while ((*pos)->__token__ == OPEN_DIV)
			(*pos) = (*pos)->p;
	}
	catch_and2(msh, pos, deep);
	return (1);
}

int	catch_or(t_msh *msh, t_cut_cmd **pos)
{
	register int	deep;

	deep = 0;
	if ((*pos)->__token__ != OR)
		return (0);
	if (msh->tools->status)
		(*pos) = (*pos)->p;
	while (msh->tools->status && (*pos)->__token__ == OPEN_DIV)
		(*pos) = (*pos)->p;
	if (((*pos)->n && (*pos)->n->__token__ == CLOSED_DIV)
		|| ((*pos)->p && (*pos)->p->__token__ == OPEN_DIV))
	{
		msh->tools->flag_map = NULL;
		flag_loop("NULL:push INIT=INIT");
	}
	while (!msh->tools->status && (*pos))
	{
		if ((*pos)->__token__ == OPEN_DIV)
			deep++;
		if ((*pos)->__token__ == AND && !deep)
			break ;
		(*pos) = (*pos)->p;
	}
	return (1);
}
