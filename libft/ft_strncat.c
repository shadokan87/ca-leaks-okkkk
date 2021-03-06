/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:55:31 by motoure           #+#    #+#             */
/*   Updated: 2021/09/21 20:37:00 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	i;
	int				y;

	y = ft_strlen(dest);
	i = 0;
	while (src[i] && i < nb)
	{
		dest[y] = src[i];
		i++;
		y++;
	}
	if (dest[y])
		dest[y] = '\0';
	return (dest);
}
