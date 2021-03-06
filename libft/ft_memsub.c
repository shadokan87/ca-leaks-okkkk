/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 09:05:41 by motoure           #+#    #+#             */
/*   Updated: 2021/09/21 20:23:40 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memsub(void **dst, void *src, size_t index, int max)
{
	unsigned char	*c_dst;
	unsigned char	*c_src;

	c_dst = (unsigned char *)*dst;
	c_src = (unsigned char *)src;
	if (max == -1)
	{
		while (*c_src)
		{
			c_dst[index] = *c_src;
			c_src++;
			index++;
		}
		c_dst[index] = *c_src;
		return ;
	}
	while (max)
	{
		c_dst[index] = *c_src;
		c_src++;
		index++;
		max--;
	}
	c_dst[index] = 0;
}
