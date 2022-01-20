/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_p_p_par.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 04:49:38 by motoure           #+#    #+#             */
/*   Updated: 2021/09/21 20:18:13 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libshell.h"

int	p_p_syntax_exceptions(t_msh *msh)
{
	return ((msh->tools->error_msg == NULL));
}

void	p_p_control_token_combination(t_msh *msh, t_cut_cmd *iterator)
{
	register int	is_redir;

	is_redir = ((iterator->__token__ >= R_REDIR
				&& iterator->__token__ <= L_REDIR));
	if ((iterator->__token__ == OPEN_DIV && iterator->n)
		&& !is_match(SYMBOL_ALLOWED_BEFORE_OPEN_DIV, ':', iterator->n->elem))
		msh->tools->error_msg
			= ft_strjoin("operand missing before: ", iterator->elem);
	else if ((iterator->__token__ == CLOSED_DIV && iterator->p)
		&& !is_match(SYMBOL_ALLOWED_AFTER_CLOSED_DIV, ':', iterator->p->elem))
		msh->tools->error_msg
			= ft_strjoin("operand missing after: ", iterator->elem);
	else if ((iterator->__token__ == AND)
		&& (is_match("&", ':', iterator->elem)))
		msh->tools->error_msg = p_near("&");
	else if ((iterator->__token__ == AND)
		&& iterator->p->__token__ == CLOSED_DIV)
		msh->tools->error_msg = p_near(")");
	if (is_redir && iterator->p && (iterator->p->__token__ == CLOSED_DIV
			|| iterator->p->__token__ == OPEN_DIV))
		msh->tools->error_msg = p_near(iterator->p->elem);
}

int	p_p_ready_to_process(t_msh *msh)
{
	t_cut_cmd	*iterator;

	iterator = msh->tools->head;
	while (iterator && !msh->tools->error_msg)
	{
		p_p_control_token_combination(msh, iterator);
		iterator = iterator->n;
	}
	return (p_p_syntax_exceptions(msh));
}

int	p_p_check_par_join(t_msh *msh)
{
	char		*to_check;
	t_cut_cmd	*ptr;

	to_check = NULL;
	ptr = msh->tools->tail;
	while (ptr)
	{
		if (ptr->__token__ != S_QUOTE && ptr->__token__ != D_QUOTE)
		{
			if (!to_check)
				to_check = ft_strdup(ptr->elem);
			else
				to_check = ft_strjoin(to_check, ft_strjoin(" ", ptr->elem));
		}
		ptr = ptr->p;
	}
	if (to_check)
		return (p_check_par(msh, to_check));
	return (0);
}
