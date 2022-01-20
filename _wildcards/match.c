/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 05:43:06 by motoure           #+#    #+#             */
/*   Updated: 2021/08/08 05:47:06 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./wildcards.h"

int	match(char *s1, char *s2, char *mode)
{
	int	st_start_with;
	int	st_contain;
	int	st_end_with;

	st_start_with = ((is_same(mode, "start_with"))
			&& ((ft_strlen(s2) >= ft_strlen(s1))
				&& (is_same((ft_strndup((s2), ft_strlen(s1))), s1))));
	st_contain = ((is_same(mode, "CONTAIN"))
			&& ft_strlen(s2) >= ft_strlen(s1)
			&& ft_strnstr(s2, s1, ft_strlen(s2)));
	st_end_with = ((is_same(mode, "end_with"))
			&& (ft_strlen(s2) >= ft_strlen(s1))
			&& (is_same(ft_strrev(ft_strndup(ft_strrev(s2),
							ft_strlen(s1))), s1)));
	if (st_start_with || st_contain || st_end_with)
		return (ft_strlen(s1));
	return (0);
}

t_cut_cmd	**match_end_with(t_msh *msh, char *str)
{
	t_cut_cmd	**ret;
	t_cut_cmd	*ls;

	ret = ft_calloc(2, sizeof(t_cut_cmd *) * 2);
	if (!ret)
		return (NULL);
	head_tail(msh, "backup");
	ls = ft_ls(".", NULL);
	while (ls)
	{
		if (match(str, ft_strdup(ls->elem), "end_with"))
			add(msh, ls->elem, ARG);
		ls = ls->n;
	}
	ret[0] = msh->tools->head;
	ret[1] = msh->tools->tail;
	head_tail(msh, "restore");
	return (ret);
}

t_cut_cmd	**match_all(t_msh *msh, char *str)
{
	t_cut_cmd	**ret;
	t_cut_cmd	*ls;

	(void)str;
	ret = ft_calloc(2, sizeof(t_cut_cmd *) * 2);
	if (!ret)
		return (NULL);
	head_tail(msh, "backup");
	ls = ft_ls(".", NULL);
	while (ls)
	{
		add(msh, ls->elem, ARG);
		ls = ls->n;
	}
	ret[0] = msh->tools->head;
	ret[1] = msh->tools->tail;
	head_tail(msh, "restore");
	return (ret);
}

t_cut_cmd	**match_start_with(t_msh *msh, char *str)
{
	t_cut_cmd	**ret;
	t_cut_cmd	*ls;

	ret = ft_calloc(2, sizeof(t_cut_cmd *) * 2);
	if (!ret)
		return (NULL);
	head_tail(msh, "backup");
	ls = ft_ls(".", "-a");
	while (ls)
	{
		if (match(str, ls->elem, "start_with"))
			add(msh, (ls->elem), ARG);
		ls = ls->n;
	}
	ret[0] = msh->tools->head;
	ret[1] = msh->tools->tail;
	head_tail(msh, "restore");
	return (ret);
}

t_cut_cmd	**match_contain(t_msh *msh, char *str)
{
	t_cut_cmd	**ret;
	t_cut_cmd	*ls;

	ret = ft_calloc(2, sizeof(t_cut_cmd *) * 2);
	if (!ret)
		return (NULL);
	head_tail(msh, "backup");
	ls = ft_ls(".", "-a");
	while (ls)
	{
		if (match(str, ls->elem, "CONTAIN"))
			add(msh, (ls->elem), ARG);
		ls = ls->n;
	}
	ret[0] = msh->tools->head;
	ret[1] = msh->tools->tail;
	head_tail(msh, "restore");
	return (ret);
}
