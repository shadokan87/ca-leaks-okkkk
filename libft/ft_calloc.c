/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:20:27 by motoure           #+#    #+#             */
/*   Updated: 2021/09/12 09:39:56 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*return_value;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 0;
	}
	return_value = gc_malloc(size * count);
	ft_memset(return_value, 0, count * size);
	return (return_value);
}
