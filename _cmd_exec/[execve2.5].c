/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [execve2.5].c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 01:44:12 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 00:51:19 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

int	get_dollar_end(char *dollar)
{
	int	i;

	i = 1;
	while ((dollar[i]))
	{
		if (dollar[i] == '$' && !(dollar[i + 1] && dollar[i + 1] == '$'))
			return (i);
		else if (!ft_isalnum(dollar[i]) && dollar[i] != '_')
			break ;
		i++;
	}
	return (i);
}

void	_place_holder_handle_expand_env(t_msh *msh, t_cut_cmd *cmd)
{
	t_cut_cmd	*iterator;
	char		*current_write;

	(void)msh;
	iterator = cmd;
	while (iterator && iterator->__token__ != AND
		&& iterator->__token__ != OR)
	{
		current_write = NULL;
		while (iterator->elem && *iterator->elem
			&& iterator->__token__ != S_QUOTE)
		{
			if (*iterator->elem == '$')
				_dollar_append_if_valid(msh,
					iterator, &current_write, &iterator->elem);
			if (iterator->elem && !(*iterator->elem == '$'))
			{
				p_putchar_str(&current_write, *iterator->elem);
				iterator->elem++;
			}
		}
		if (iterator->__token__ != S_QUOTE)
			iterator->elem = current_write;
		iterator = iterator->p;
	}
}

void	_dollar_handle_append_failure(t_msh *msh,
			t_cut_cmd *iterator, char **current_write, char **elem_ptr)
{
	t_cut_cmd	*home_is_set;

	home_is_set = get_env_of(msh->envp, "HOME");
	if (*elem_ptr && *elem_ptr[0] == '?')
	{
		*elem_ptr = *elem_ptr + 1;
		if (!*current_write)
			*current_write = ft_itoa(msh->tools->status);
		else
			*current_write = ft_strjoin(*current_write,
					ft_itoa(msh->tools->status));
	}
	if (!(*current_write))
	{
		if (is_same(iterator->elem, "~") && home_is_set)
			iterator->elem = get_val_from_var(home_is_set);
		else
		{
			if (iterator->n)
				iterator->n->p = NULL;
			else
				iterator = NULL;
		}
	}
}

void	_dollar_append_if_valid(t_msh *msh,
			t_cut_cmd *iterator, char **current_write, char **elem_ptr)
{
	char	*found;
	char	*dollar;

	found = NULL;
	dollar = ft_strtrim(ft_strndup(iterator->elem,
				get_dollar_end(iterator->elem)), "$");
	*elem_ptr = iterator->elem + get_dollar_end(iterator->elem);
	if (is_same(*elem_ptr, ""))
		*elem_ptr = NULL;
	found = get_val_from_var(get_env_of(msh->envp, dollar));
	if (!found)
	{
		_dollar_handle_append_failure(msh, iterator, current_write, elem_ptr);
		if (*elem_ptr && !**elem_ptr)
			*elem_ptr = NULL;
	}
	else if (*current_write)
		*current_write = ft_strjoin(*current_write, found);
	else
		*current_write = ft_strdup(found);
}
