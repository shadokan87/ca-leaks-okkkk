/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_p_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 04:39:41 by motoure           #+#    #+#             */
/*   Updated: 2021/09/21 01:16:24 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libshell.h"

int	p_quote_to_struct(t_msh *msh, char *str)
{
	int		flag_tmp;
	char	*tmp;

	tmp = NULL;
	flag_tmp = -1;
	if (c_is_present(str, '\"'))
		flag_tmp = ft_atoi(flag("get CINDEX"));
	else
		p_putchar_str(&tmp, '\'');
	p_quote_to_struct2(flag_tmp, str, &tmp);
	if (is_same(str, ""))
		return (0);
	if (tmp[0] == '\'')
		add(msh, del_quotes(str, S_QUOTE, 0), S_QUOTE);
	else
		add(msh, del_quotes(str, D_QUOTE, 0), D_QUOTE);
	return (1);
}

int	split_quotes(t_msh *msh, char *ptr)
{
	char	*str;
	char	*str2;

	str = NULL;
	str2 = NULL;
	ptr += get_next_quote2(ptr, &str);
	p_str_to_struct(msh, ft_strtrim(str, " "));
	if (get_next_quote(ptr, 0) != -1)
		ptr = str_modulo(ptr, &str2, get_next_quote(ptr, 0));
	if (str2 && is_same(ft_strtrim(str2, " "), ""))
	{
		if (!(p_check_symbols(msh, str2)))
			return (0);
		p_str_to_struct(msh, ft_strtrim(p_escape_line(msh, str2), " "));
	}
	if (ptr && !*ptr)
		return (1);
	if (get_next_quote(ft_strtrim(ptr, " "), 0) != -1)
		return (split_quotes(msh, ft_strtrim(ptr, " ")));
	if (!(p_check_symbols(msh, ptr)))
		return (0);
	ptr = p_escape_line(msh, ptr);
	p_str_to_struct(msh, ptr);
	return (1);
}

int	get_split_deep(char **split, char c)
{
	int	deep;
	int	i;
	int	y;

	deep = 0;
	i = 0;
	y = 0;
	while (split[i])
	{
		while (split[i][y])
		{
			if (split[i][y] == c)
				deep++;
			y++;
		}
		if (deep % 2 == 0)
			break ;
		y = 0;
		i++;
	}
	return (deep);
}

int	split_quotes_init(t_msh *msh)
{
	char	*ptr;
	char	*str;
	char	*concat;

	concat = NULL;
	ptr = msh->jobs->have_been_read;
	ptr = str_modulo(ptr, &str, get_next_quote(ptr, 0));
	if (!(p_check_symbols(msh, ft_strjoin(str, ptr))))
		return (0);
	if (flag("QUOTE_CONCAT_PREV == true")
		&& !flag("push QUOTE_CONCAT_PREV=false"))
	{
		str = ft_strrev(str);
		while (*str != ' ')
		{
			p_putchar_str(&concat, *str);
			str++;
		}
		ptr = ft_strjoin(ft_strrev(concat), ptr);
		str = ft_strtrim(ft_strrev(str), " ");
	}
	str = p_escape_line(msh, str);
	p_str_to_struct(msh, ft_strtrim(str, " "));
	return (split_quotes(msh, ptr));
}

int	p_check_quotes(t_msh *msh)
{
	int	i;
	int	mark_double;
	int	mark_single;

	i = 0;
	mark_double = 0;
	mark_single = 0;
	while (msh->jobs->have_been_read[i])
	{
		if (msh->jobs->have_been_read[i] == '\"' && mark_single % 2 == 0)
			mark_double++;
		if (msh->jobs->have_been_read[i] == '\'' && mark_double % 2 == 0)
			mark_single++;
		i++;
	}
	if (mark_double % 2 != 0 || mark_single % 2 != 0)
	{
		msh->tools->error_msg = ft_strdup("dquote not supported");
		return (0);
	}
	if (mark_double || mark_single)
		return (split_quotes_init(msh));
	return (1);
}
