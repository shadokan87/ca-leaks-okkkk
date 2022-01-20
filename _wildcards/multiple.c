/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 05:43:10 by motoure           #+#    #+#             */
/*   Updated: 2021/09/21 20:05:01 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./wildcards.h"

static int	label_cmp(t_cut_cmd *wild, char **tmp, char *str,
int (*caller)(t_cut_cmd *wild, char *str, char *__goto))
{
	int	ret;

	*tmp = ft_strtrim(wild->elem, "*");
	if (wild->wild_card_type == W_CONTAIN)
		ret = match(*tmp, ft_strdup(str), "CONTAIN");
	else
		ret = match(*tmp, ft_strdup(str), "start_with");
	if (!ret)
		return (0);
	else
		str += ret;
	wild = wild->p;
	*tmp = ft_strtrim(wild->elem, "*");
	if (list_len(wild) != 1)
		return (caller(wild, str, "INC"));
	while (wild->wild_card_type == W_START_WITH && *str != **tmp)
		str++;
	if (wild->wild_card_type == W_START_WITH && *str && *str == **tmp)
		return (1);
	return (match(*tmp, str, "end_with"));
}

static	int	label_inc(t_cut_cmd *wild, char **tmp, char *str,
int (*caller)(t_cut_cmd *wild, char *str, char *__goto))
{
	*tmp = ft_strtrim(wild->elem, "*");
	while (*str != **tmp)
		str++;
	if (!*str)
		return (0);
	return (caller(wild, str, "CMP"));
}

static	int	solve_match(t_cut_cmd *wild, char *str, char *__goto)
{
	int			ret;
	char		*tmp;
	int			(*self)(t_cut_cmd *wild, char *str, char *__goto);

	(void)ret;
	self = &solve_match;
	if (is_same(__goto, "CMP"))
		return (label_cmp(wild, &tmp, str, self));
	else if (is_same(__goto, "INC"))
		return (label_inc(wild, &tmp, str, self));
	return (1);
}

void	substitute_wildcards_multiple(t_msh *msh, t_cut_cmd **pos)
{
	t_cut_cmd	*ls;

	ls = ft_ls(".", "-a");
	head_tail(msh, "backup");
	while (ls)
	{
		if (solve_match((*pos)->tail_wild_card, ft_strdup(ls->elem), "CMP"))
			add(msh, ls->elem, ARG);
		ls = ls->n;
	}
	(*pos)->tail_wild_card = msh->tools->tail;
	(*pos)->head_wild_card = msh->tools->head;
	head_tail(msh, "restore");
}
