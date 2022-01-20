/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_p_quotes_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 04:41:57 by motoure           #+#    #+#             */
/*   Updated: 2021/09/15 02:36:05 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libshell.h"

int	get_next_quote(char *str, int i)
{
	if (!str)
		return (-1);
	while (str[i] && str[i] != '\"' && str[i] != '\'')
		i++;
	if (!str[i])
		i = -1;
	if (i > 0 && str[i - 1] != ' ')
	{
		if (!(str[i + 1] && str[i + 1] == str[i]))
			flag("push QUOTE_CONCAT_PREV=true");
	}
	if (i > 0 && str[i + 1] && (str[i + 1] != ' '))
		flag("push QUOTE_CONCAT_NEXT=true");
	return (i);
}
