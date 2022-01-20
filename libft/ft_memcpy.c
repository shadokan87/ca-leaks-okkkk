/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:21:29 by motoure           #+#    #+#             */
/*   Updated: 2021/09/21 20:23:16 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strcpy(char *src, char *dst)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned long		i;
	char				*return_value;
	char				*casted_dst;
	char				*casted_src;

	casted_dst = (char *)dst;
	casted_src = (char *)src;
	return_value = (char *)dst;
	i = 0;
	if (dst == src)
		return (dst);
	while (i < n)
	{
		casted_dst[i] = casted_src[i];
		i++;
	}
	return (return_value);
}
