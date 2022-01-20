/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_co.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:55:20 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 20:55:21 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libshell.h"

t_gc	*g_gc = NULL;

void	gc_init(void)
{
	g_gc = malloc(sizeof(t_gc));
	if (!g_gc)
		return ;
	g_gc->normal = NULL;
	g_gc->mute = NULL;
	g_gc->dst = 0;
}

int	free_normal_target(void *target)
{
	t_addr	*ptr;
	t_addr	*ptr2;

	if (!g_gc->normal)
		return (0);
	ptr = g_gc->normal;
	while (ptr)
	{
		if (ptr->n && ptr->n->g == target)
		{
			ptr2 = ptr->n;
			ptr->n = ptr2->n;
			free(ptr2->g);
			free(ptr2);
			return (1);
		}
		ptr = ptr->n;
	}
	return (0);
}

int	free_mute_target(void *target)
{
	t_addr	*ptr;
	t_addr	*ptr2;

	if (!g_gc->mute)
		return (0);
	ptr = g_gc->mute;
	while (ptr)
	{
		if (ptr->n && ptr->n->g == target)
		{
			ptr2 = ptr->n;
			ptr->n = ptr2->n;
			free(ptr2->g);
			free(ptr2);
			return (1);
		}
		ptr = ptr->n;
	}
	return (0);
}

void	*to_gc(void ***g)
{
	gc_push(g);
	return (g);
}

void	*gc_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (size > 0 && !ret)
	{
		write(2, "GC_MALLOC_ERROR\n", 16);
		gc("collect -all");
		exit (0);
	}
	gc_push(ret);
	return (ret);
}
