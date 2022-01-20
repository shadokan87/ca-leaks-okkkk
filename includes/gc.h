/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 02:42:56 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/15 00:44:37 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include "./libshell.h"

typedef struct s_addr
{
	void							*g;
	int								immune;
	struct s_addr					*n;
	struct s_addr					*p;
}									t_addr;

typedef struct s_garbage_collector
{
	void							*to_ignore;
	int								dst;
	t_addr							*normal;
	t_addr							*mute;
	t_msh							*msh_ptr;
	void							(*spawn_prompt)(t_msh *msh);
}									t_gc;

extern t_gc	*g_gc;

void	gc(char *instr);

void	free_normal(void);

void	free_mute(void);

void	gc_init(void);

void	*gc_malloc(size_t size);

void	gc_free(void *ptr);

void	gc_free(void *ptr);

void	gc_free_calloc(char **_calloc);

void	gc(char *instr);

int		free_mute_target(void *target);

int		free_normal_target(void *target);

int		collect(int mode);

int		push_to_mute(t_addr *new);

int		gc_push(void ***g);

void	*to_gc(void ***g);

int		push_to_normal(t_addr *new);

#endif
