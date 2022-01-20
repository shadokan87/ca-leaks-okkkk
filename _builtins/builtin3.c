/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:02:40 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 00:39:25 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

static int	swaping(t_msh **msh, t_cut_cmd *env, char *new, size_t len)
{
	(void)len;
	while (env)
	{
		if (!ft_strncmp(new, (env)->elem, (len - 1)))
		{
			gc("pause");
			(env)->elem = ft_strdup(new);
			gc("resume");
			env->__token__ = _UNASSIGNED;
			return (SUCCESS);
		}
		(env) = (env)->n;
	}
	gc("pause");
	add_env(msh, new, 0);
	gc("resume");
	return (SUCCESS);
}

static void	swaping2(t_msh **msh, t_cut_cmd *env, char *new)
{
	int		match;
	size_t	len;

	match = 0;
	len = ft_strlen(new);
	while (env && !match)
	{
		if (!ft_strncmp(env->elem, new, len))
			match = 1;
		env = env->n;
	}
	if (!match)
	{
		gc("pause");
		add_env(msh, new, ENV_SOLO);
		gc("resume");
	}
}

int	swap_env(t_msh **msh, char *new)
{
	t_cut_cmd	*env;
	size_t		len;
	int			match;

	len = 0;
	match = 0;
	env = (*msh)->env->head;
	while (new[len] && !match)
	{
		if (new[len] == '=')
			match = 1;
		len++;
	}
	if (new[len])
		swaping(msh, env, new, len);
	else
	{
		swaping2(msh, env, new);
		return (SUCCESS);
	}
	return (ERROR);
}

/*
t_cut_cmd	*bubble_sort(t_cut_cmd *bulle)
{
	size_t		len;
	t_cut_cmd	*bs;
	t_cut_cmd	*bs1;
	t_cut_cmd	*tmp;

	if (!bulle || !bulle->n)
		return (NULL);
	bs = (t_cut_cmd *)malloc(sizeof(t_cut_cmd));
	bs = bulle;
	bs1 = bulle->n;
	while (bs && bs1)
	{
		while (bs1)
		{
			len = ft_strlen(bs1->elem);
			if (ft_strncmp(bs->elem, bs1->elem, len) > 0)
			{
				tmp = bs;
				bs = bs1;
				bs1 = tmp;
			}
			bs1 = bs1->n;
		}
		bs = bs->n;
		bs1 = bs->n;
	}
	return (bs);
}
*/
int	print_export(t_msh *msh, t_cut_cmd *env,
	char **env_split, char *to_print)
{
	if (!msh->tools->fdout)
		msh->tools->fdout = 1;
	while (env)
	{
		if (ft_strchr(env->elem, '=') && env->__token__ != ENV_SOLO)
		{
			env_split = ft_split(env->elem, '=');
			to_print = ft_strjoin("declare -x ", env_split[0]);
			to_print = ft_strjoin(to_print, "=\"");
			to_print = ft_strjoin(to_print, env_split[1]);
			to_print = ft_strjoin(to_print, "\"");
			ft_putendl_fd(to_print, msh->tools->fdout);
		}
		else
		{
			ft_putstr_fd("declare -x ", msh->tools->fdout);
			ft_putendl_fd(env->elem, msh->tools->fdout);
		}
		env = env->n;
	}
	return (SUCCESS);
}

int	is_env(t_msh **msh, char *to_pop)
{
	char		**sp;
	t_cut_cmd	*head;

	if (!msh || !to_pop)
		return (0);
	head = (*msh)->env->head;
	while (head)
	{
		sp = ft_split(head->elem, '=');
		if (sp && (!(ft_strncmp(to_pop, sp[0], (size_t)ft_strlen(sp[0])))))
		{
			(*msh)->tools->tmp_node = head;
			return (SUCCESS);
		}
		head = head->n;
	}
	return (ERROR);
}
