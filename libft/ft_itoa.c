/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 01:16:16 by motoure           #+#    #+#             */
/*   Updated: 2021/09/21 20:22:00 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	count(int n)
{
	int	count;

	count = 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static	char	*handle_spe(int n)
{
	if (n == 0)
		return (ft_strdup("0"));
	else
		return (ft_strdup("-2147483648"));
}

static	int	set_negative(int n)
{
	int	negative;

	if (n > 0)
		negative = 0;
	else
		negative = 1;
	return (negative);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*ret;
	int		negative;

	if (n == -2147483648 || n == 0)
		return (handle_spe(n));
	negative = set_negative(n);
	if (negative)
		n = n * -1;
	i = 0;
	if (negative)
		ret = gc_malloc(sizeof(char) * count(n) + 2);
	else
		ret = gc_malloc(sizeof(char) * count(n) + 1);
	while (n)
	{
		ret[i] = n % 10 + 48;
		n /= 10;
		i++;
	}
	if ((negative))
		ret[i++] = '-';
	ret[i] = '\0';
	return (ft_strrev(ret));
}
