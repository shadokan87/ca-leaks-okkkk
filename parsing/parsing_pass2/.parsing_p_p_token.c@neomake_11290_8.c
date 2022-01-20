/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_p_p_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 05:14:09 by motoure           #+#    #+#             */
/*   Updated: 2021/08/30 05:14:20 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libshell.h"

t_token	p_p_determine_symbol(char *elem)
{
	static char	**lookup_table;
	int			*token_index;
	int			table_len;
	int			i;

	i = 0;
	lookup_table = ft_split(SYMBOL_DETERMINE, ' ');
	table_len = split_len(lookup_table);
	token_index = gc_malloc(sizeof(int) * table_len);
	if (!token_index)
		return (0);
	table_len = PIPE;
	while (table_len < _END)
	{
		token_index[i] = table_len;
		table_len++;
		i++;
	}
	i = 0;
	while (lookup_table[i] && !is_match(lookup_table[i], ' ', elem))
		i++;
	if (lookup_table[i])
		return (token_index[i]);
	return (_UNASSIGNED);
}

t_token	p_p_determine_cmd(char *elem, int cmd_re_eval)
{
	(void)cmd_re_eval;
	if (is_builtin(elem) && cmd_re_eval)
		return (C_BUILTIN);
	else if (elem[0] == '-')
		return (OPTION);
	else if (!cmd_re_eval)
		return (ARG);
	return (C_ENV);
}

int	p_p_determine_token(t_msh *msh)
{
	t_cut_cmd	*iter;
	int			cmd_re_eval;

	cmd_re_eval = 1;
	iter = msh->tools->tail;
	while (iter && !msh->tools->error_msg)
	{
		if (iter->__token__ == _UNASSIGNED
			&& is_match(SYMBOL_DETERMINE, ' ', iter->elem))
		{
			iter->__token__ = p_p_determine_symbol(iter->elem);
			if (iter->__token__ == OPEN_DIV || iter->__token__ == CLOSED_DIV
				|| iter->__token__ == OR || iter->__token__ == AND)
				cmd_re_eval = 1;
		}
		else if (iter->__token__ == _UNASSIGNED)
		{
			iter->__token__ = p_p_determine_cmd(iter->elem, cmd_re_eval);
			cmd_re_eval = 0;
		}
		iter = iter->p;
	}
	return (1);
}
