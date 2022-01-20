/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 02:11:45 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 01:03:16 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

void	inc_ret(t_cut_cmd *cmd, int *ret)
{
	(void)cmd;
	if (cmd->__token__ == WILD_CARD && cmd->tail_wild_card)
		*ret += list_len(cmd->tail_wild_card);
	else
		*ret += 1;
}

int	strdup_wildcard_or_elem(t_cut_cmd *tail, char ***args, int i)
{
	t_cut_cmd	*iterator;

	if (tail->__token__ == WILD_CARD && tail->tail_wild_card)
	{
		iterator = tail->tail_wild_card;
		while (iterator)
		{	
			(*args)[i] = ft_strdup(iterator->elem);
			iterator = iterator->p;
			i++;
		}
		return (list_len(tail->tail_wild_card));
	}
	if (tail->elem)
		(*args)[i] = ft_strdup(tail->elem);
	return (1);
}

t_cut_cmd	*is_in_div(t_cut_cmd *pos)
{
	t_cut_cmd	*iterator;

	iterator = pos;
	while (iterator)
	{
		if (iterator->__token__ == OPEN_DIV)
			return (iterator->p);
		iterator = iterator->n;
	}
	return (NULL);
}

void	init_pos(t_cut_cmd *tail, t_cut_cmd **pos)
{
	while (tail->__token__ == OPEN_DIV)
		tail = tail->p;
	(*pos) = tail;
}
