/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 13:11:46 by motoure           #+#    #+#             */
/*   Updated: 2021/09/21 20:34:00 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	count_word(char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && str[i] == sep)
		i++;
	while (str[i])
	{
		count++;
		while (str[i] && str[i] != sep)
			i++;
		while (str[i] && str[i] == sep)
			i++;
	}
	return (count);
}

char	*skip_sep(char *str, char c)
{
	while (*str && *str == c)
		str++;
	return (str);
}

int	bad_malloc(char **ret, int i)
{
	if (!ret[i])
	{
		while (--i > -1)
			free(ret[i]);
		free(ret);
		return (1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char		*str;
	char		**ret;
	int			i;
	int			c_len;
	const int	sep_count = count_word((char*)s, c);

	ret = ft_calloc(sep_count + 1, sizeof(char *));
	str = (char *)s;
	i = 0;
	if (!ret)
		return (NULL);
	str = skip_sep(str, c);
	while (i < sep_count)
	{
		c_len = get_c_index(str, c);
		if (c_len == -1)
			c_len = ft_strlen(str);
		ret[i] = ft_strndup(str, c_len);
		if (bad_malloc(ret, i))
			return (NULL);
		str += c_len;
		str = skip_sep(str, c);
		i++;
	}
	return (ret);
}
