/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 19:41:32 by motoure           #+#    #+#             */
/*   Updated: 2021/09/21 20:44:59 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*return_value;

	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
	{
		return_value = gc_malloc(sizeof(char) * 1);
		if (!return_value)
			return (0);
		if (!(return_value[0] == '\0'))
			return_value[0] = '\0';
		return (return_value);
	}
	return_value = gc_malloc(sizeof(char) * len + 1);
	if (!return_value)
		return (0);
	ft_memcpy(return_value, s + start, len);
	return_value[len] = '\0';
	return (return_value);
}
