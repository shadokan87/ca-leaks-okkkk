/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 02:38:31 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/11 19:16:01 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

int	is_empty_env(t_cut_cmd *env)
{
	if (!env || env == NULL)
		return (SUCCESS);
	return (ERROR);
}

int	create_env_list(t_msh **msh, char *content)
{
	t_cut_cmd	*new_block;

	if (is_empty_env((*msh)->env->head))
	{
		new_block = (t_cut_cmd *)gc_malloc(sizeof(t_cut_cmd));
		if (!new_block)
			return (-1);
		new_block->elem = content;
		new_block->__token__ = _UNASSIGNED;
		new_block->is_last = 0;
		new_block->p = NULL;
		new_block->n = NULL;
		(*msh)->env->head = new_block;
		(*msh)->env->tail = new_block;
		(*msh)->env->size = 1;
		return (SUCCESS);
	}
	return (ERROR);
}

int	add_env(t_msh **msh, char *content, int mode)
{
	t_cut_cmd	*new_block;

	new_block = (t_cut_cmd *)gc_malloc(sizeof(t_cut_cmd));
	if (!new_block)
		return (-1);
	if (!(ft_strchr(content, '=') + 1))
		new_block->elem = ft_strjoin(content, "=\"\"\n");
	else
		new_block->elem = ft_strdup(content);
	new_block->n = NULL;
	new_block->p = (*msh)->env->tail;
	if (mode)
		new_block->__token__ = ENV_SOLO;
	else
		new_block->__token__ = _UNASSIGNED;
	(*msh)->env->tail->n = new_block;
	(*msh)->env->tail = new_block;
	(*msh)->env->size++;
	return (SUCCESS);
}

int	add_to_env(t_cut_cmd **target, char *elem, t_token __token__)
{
	t_cut_cmd	*ret;

	ret = fill(elem, __token__);
	if (!*target)
	{
		*target = ret;
		return (1);
	}
	ret->n = *target;
	(*target)->p = ret;
	*target = ret;
	return (1);
}

t_cut_cmd	*get_env_of(t_cut_cmd *target, char *to_find)
{
	t_cut_cmd	*ptr;
	char		*current_var;

	ptr = target;
	current_var = NULL;
	if (!ptr)
		return (NULL);
	while (ptr)
	{
		current_var = ft_split(ptr->elem, '=')[0];
		if (is_same(current_var, to_find))
			return (ptr);
		ptr = ptr->n;
	}
	return (NULL);
}
