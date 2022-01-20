/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_co2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:55:30 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 20:55:30 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libshell.h"

void	free_mute(void)
{
	t_addr	*ptr;

	if (!g_gc->mute)
		return ;
	while (g_gc->mute)
	{
		ptr = g_gc->mute;
		g_gc->mute = g_gc->mute->n;
		free(ptr->g);
		free(ptr);
	}
	free(g_gc->mute);
	g_gc->mute = NULL;
}

void	free_normal(void)
{
	t_addr	*ptr;

	while (g_gc->normal)
	{
		ptr = g_gc->normal;
		g_gc->normal = g_gc->normal->n;
		free(ptr->g);
		free(ptr);
	}
	free(g_gc->normal);
	g_gc->normal = NULL;
}

int	collect(int mode)
{
	if (!g_gc)
		return (0);
	if (!mode || mode == 2)
		free_normal();
	if (mode || mode == 2)
		free_mute();
	if (mode == 2)
	{
		free(g_gc);
		g_gc = NULL;
	}
	return (1);
}

void	gc(char *instr)
{
	if (!g_gc)
		gc_init();
	if (is_same(instr, "pause"))
		g_gc->dst = 1;
	else if (is_same(instr, "resume"))
		g_gc->dst = 0;
	else if (is_same(instr, "collect"))
		collect(0);
	else if (is_same(instr, "collect -mute"))
		collect(1);
	else if (is_same(instr, "collect -all"))
		collect(2);
	else
	{
		write(2, "GC_BAD_INSTR", 12);
		exit (0);
	}
}

int	push_to_mute(t_addr *new)
{
	if (!g_gc->mute)
	{
		g_gc->mute = new;
		return (1);
	}
	if (g_gc->dst)
	{
		new->n = g_gc->mute;
		g_gc->mute->p = new;
		g_gc->mute = new;
		return (1);
	}
	return (1);
}
