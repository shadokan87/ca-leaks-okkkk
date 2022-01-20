/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 05:43:15 by motoure           #+#    #+#             */
/*   Updated: 2021/08/08 05:43:18 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./wildcards.h"

void	substitute_wildcards(t_msh *msh, t_cut_cmd **pos)
{
	t_cut_cmd	**ret;

	(void)pos;
	ret = NULL;
	if ((*pos)->tail_wild_card->wild_card_type == W_START_WITH)
		ret = match_start_with(msh, ft_strtrim((*pos)->elem, "*"));
	else if ((*pos)->tail_wild_card->wild_card_type == W_CONTAIN)
		ret = match_contain(msh, ft_strtrim((*pos)->elem, "*"));
	else if ((*pos)->tail_wild_card->wild_card_type == W_END_WITH)
		ret = match_end_with(msh, ft_strtrim((*pos)->elem, "*"));
	else if ((*pos)->tail_wild_card->wild_card_type == W_ALL)
		ret = match_all(msh, NULL);
	if (ret)
	{
		(*pos)->head_wild_card = ret[0];
		(*pos)->tail_wild_card = ret[1];
	}
}
