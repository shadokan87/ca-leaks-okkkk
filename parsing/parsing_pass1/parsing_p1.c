/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_p1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 01:17:58 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 01:18:14 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libshell.h"

void	re_eval_quote2(t_cut_cmd *pos)
{
	t_cut_cmd	*iterator;

	iterator = pos;
	while (iterator)
	{
		if ((iterator->__token__ == S_QUOTE
				|| iterator->__token__ == D_QUOTE)
			&& iterator->elem)
		{
			if (iterator->elem[0] == '-')
				iterator->__token__ = OPTION;
			else
				iterator->__token__ = ARG;
		}
		iterator = iterator->p;
	}
}

void	re_eval_quote(t_cut_cmd *pos)
{
	if (pos->__token__ == D_QUOTE)
	{
		pos->elem = ft_strtrim(pos->elem, "\"");
		if (is_builtin(pos->elem))
			pos->__token__ = C_BUILTIN;
		else
			pos->__token__ = C_ENV;
	}
	if (pos->__token__ == S_QUOTE)
	{
		pos->elem = ft_strtrim(pos->elem, "\'");
		if (is_builtin(pos->elem))
			pos->__token__ = C_BUILTIN;
		else
			pos->__token__ = C_ENV;
	}
	if (pos->p)
		re_eval_quote2(pos->p);
}

char	*p_near(char *str)
{
	char	*ret;
	char	*ret2;

	if (!ft_strncmp(str, "endl", ft_strlen(str)))
		ret2 = ft_strdup("\\n");
	else
		ret2 = ft_strndup(str, 1);
	ret = ft_strjoin("parse error near '", ret2);
	ret = ft_strjoin(ret, "'");
	return (ret);
}
