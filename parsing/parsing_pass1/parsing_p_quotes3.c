/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_p_quotes3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:21:38 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/09 21:51:57 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libshell.h"

static int	gnq2_cut(char *src, int end)
{
	if (flag("QUOTE_CONCAT_NEXT == true")
		&& !flag("push QUOTE_CONCAT_NEXT=false"))
	{
		while (src[end])
		{
			if (src[end + 1] == ' '
				|| !src[end + 1]
				|| is_symbol(src[end + 1])
				|| src[end + 1] == '('
				|| src[end + 1] == ')')
				break ;
			end++;
		}
	}
	return (end);
}

int	get_next_quote2(char *src, char **dst)
{
	int		start;
	int		start2;
	int		end;
	char	*ret;

	start = get_next_quote(src, 0);
	start2 = start;
	if (flag("QUOTE_CONCAT_PREV == true")
		&& !flag("push QUOTE_CONCAT_PREV=false"))
	{
		start2 = start;
		while (start > 0 && src[start - 1] != ' ')
			start--;
	}
	if (start == -1)
		return (-1);
	end = get_next_quote(src, start2 + 1);
	while ((src[end] != src[start2]))
		end++;
	if (src[end + 1] && src[end + 1] == src[start2])
		end = get_next_quote(src, end + 2);
	end = gnq2_cut(src, end);
	ret = ft_strndup(src + start, end + 1);
	*dst = ret;
	return (end + 1);
}

void	p_quote_to_struct2(int flag_tmp, char *str, char **tmp)
{
	if (flag_tmp >= 0 && c_is_present(str, '\'')
		&& ft_atoi(flag("get CINDEX")) < flag_tmp)
		p_putchar_str(tmp, '\'');
	else if (flag_tmp >= 0)
		p_putchar_str(tmp, '\"');
}
