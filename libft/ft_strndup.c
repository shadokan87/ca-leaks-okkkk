/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:37:30 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 20:37:31 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int size)
{
	char	*dst;
	int		i;

	i = 0;
	if (size > ft_strlen(s1))
		size = ft_strlen(s1);
	dst = gc_malloc(sizeof(char) * size + 1);
	if (dst == NULL)
		return (0);
	while (s1[i] && i < size)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
