/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_internal_ls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 22:32:13 by motoure           #+#    #+#             */
/*   Updated: 2021/08/31 01:39:27 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

/*
void	print_list_msg(t_cut_cmd *print, char *message)
{
	while (print)
	{
		if (message)
		{
			ft_putstr_fd(ft_strjoin(message, ": "), 1);
			ft_putstr_fd("\n", 1);
		}
		ft_putstr_fd(print->elem, 1);
		ft_putstr_fd("\n", 1);
		print = print->n;
	}
}
*/

char	*flag(char *instr)
{
	static t_cut_cmd	*flags;
	t_cut_cmd			*try;
	char				*to_add;

	if (is_same(instr, "print"))
		print_list_msg(flags, "\nFLAG");
	if (is_same("status", instr))
		return ((char *)flags);
	to_add = ft_split(instr, ' ')[1];
	if (is_same(ft_split(instr, ' ')[0], "push"))
	{
		gc("pause");
		try = get_env_of(flags, to_add);
		if (try)
			try->elem = to_add;
		else if (ft_split(instr, ' ')[0])
			add_to_env(&flags, to_add, _UNASSIGNED);
		gc("resume");
	}
	else if (is_same(ft_split(instr, ' ')[0], "get"))
		return (get_val_from_var(get_env_of(flags, to_add)));
	return (NULL);
}

t_cut_cmd	*ft_ls(char *path, char *options)
{
	struct dirent	*de;
	DIR				*dr;
	char			*tmp;
	t_cut_cmd		*concat;

	(void)concat;
	if (path)
		dr = opendir(path);
	else
		dr = opendir(".");
	concat = NULL;
	while (dr != NULL && ft_readdir(&de, dr))
	{
		tmp = ft_strdup(de->d_name);
		if (!is_same(options, "-a") && tmp[0] == '.')
			continue ;
		else
			add_to_env(&concat, tmp, _UNASSIGNED);
		tmp = NULL;
	}
	if (dr)
		closedir(dr);
	return (concat);
}
