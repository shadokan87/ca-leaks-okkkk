/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 01:39:34 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/20 22:13:06 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

int	print_env(t_msh *msh, t_cut_cmd *target)
{
	(void)msh;
	if (!target)
	{
		append_error(msh, target, "Env is empty", 1);
		return (0);
	}
	while (target)
	{
		if (target->__token__ != ENV_SOLO)
			printf("%s\n", target->elem);
		target = target->n;
	}
	return (1);
}

int	ft_readdir(struct dirent **de, DIR *dr)
{
	*de = readdir(dr);
	return ((*de != NULL));
}

void	ft_open(int *ret, int fd)
{
	if (*ret != -1 && *ret != 0 && *ret != 1)
		close(*ret);
	if (fd != -1)
		*ret = fd;
}

void	builtins_cut(t_msh *msh, t_cut_cmd *cmd,
		int (**f_p_builtin)(t_msh *msh, t_cut_cmd *cmd))
{
	int			index_of_cmd;

	index_of_cmd = is_match2(BUILTIN_LIST, ' ', cmd->elem);
	if (index_of_cmd != -1)
	{
		_place_holder_handle_wildcards(msh, cmd);
		f_p_builtin[index_of_cmd](msh, cmd);
	}
}

void	echo_print_wildcard(t_cut_cmd *wild, t_cut_cmd *iterator)
{
	while (wild)
	{
		if (wild->p || iterator->p)
			printf("%s ", wild->elem);
		else
			printf("%s", wild->elem);
		wild = wild->p;
	}
}
