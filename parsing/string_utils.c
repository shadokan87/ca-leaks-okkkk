/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 01:50:00 by motoure           #+#    #+#             */
/*   Updated: 2021/09/09 20:55:58 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

int	is_symbol(char c)
{
	char	**symbols;
	int		i;

	i = 0;
	symbols = ft_split(SYMBOL_LIST, ':');
	while (symbols[i])
	{
		if (symbols[i][0] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_quote(char c, char type)
{
	if (c == type)
		return (1);
	return (0);
}

void	p_putchar_str(char **str, char c)
{
	char	*ptr;
	char	*tmp;

	ptr = *str;
	tmp = NULL;
	if (!ptr)
	{
		ptr = ft_strdup("c");
		if (!ptr)
			return ;
		ptr[0] = c;
		*str = ptr;
		return ;
	}
	tmp = ft_strjoin(*str, "c");
	tmp[ft_strlen(tmp) - 1] = c;
	*str = tmp;
}

t_cut_cmd	*fill(char *elem, t_token __token__)
{
	t_cut_cmd	*ret;

	ret = gc_malloc(sizeof(t_cut_cmd));
	ret->is_last = 0;
	ret->wild_card_type = -1;
	ret->tail_wild_card = NULL;
	ret->head_wild_card = NULL;
	if (!elem)
		ret->elem = ft_strdup("");
	else
		ret->elem = ft_strdup(elem);
	ret->__token__ = __token__;
	ret->n = NULL;
	ret->p = NULL;
	ret->fd_flag = 0;
	return (ret);
}

int	add(t_msh *msh, char *elem, t_token __token__)
{
	t_cut_cmd	*ret;

	ret = fill(elem, __token__);
	if (!msh->tools->head)
	{
		msh->tools->head = ret;
		msh->tools->tail = msh->tools->head;
		return (1);
	}
	ret->n = msh->tools->head;
	msh->tools->head->p = ret;
	msh->tools->head = ret;
	return (1);
}
