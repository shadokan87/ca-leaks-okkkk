/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 02:31:47 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 20:02:51 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

int	_placeholder_handle_cmd(t_msh *msh)
{
	t_cut_cmd	*pos;

	if (msh->tools->error_msg)
		return (0);
	init_pos(msh->tools->tail, &pos);
	handle_cmd(msh, pos);
	msh->tools->flag_map = NULL;
	flag_loop("NULL:push INIT=INIT");
	return (1);
}

void	move_pos(t_msh *msh, t_cut_cmd **pos)
{
	while ((*pos))
	{
		if ((*pos)->__token__ == AND
			|| (*pos)->__token__ == OR)
			break ;
		(*pos) = (*pos)->p;
	}
	ft_open(&msh->tools->fdout, -1);
}

static void	map_flags(t_msh *msh, t_cut_cmd *pos, int inserted, int insert_pos)
{
	t_cut_cmd	*iterator;

	if (msh->tools->flag_map || !is_in_div(pos))
		return ;
	iterator = pos;
	msh->tools->flag_map = ft_calloc(list_len(pos),
			sizeof(t_cut_cmd *) * list_len(pos));
	while (iterator)
	{
		if (is_in_div(iterator))
		{
			if (scope_contain_redir(iterator) == _UNASSIGNED)
			{
				if ((iterator->__token__ == C_BUILTIN
						|| iterator->__token__ == C_ENV) && !inserted)
				{
					msh->tools->flag_map[insert_pos] = iterator;
					inserted = 1;
					insert_pos++;
				}
			}
		}
		iterator = iterator->p;
	}
}

static void	simple_exec_placeholder(t_msh *msh, t_cut_cmd *pos)
{
	if (is_same("exit", pos->elem))
		builtin_exit(msh, pos);
	else if ((pos->p && (pos->p->__token__ == ARG
				|| pos->p->__token__ == OPTION)
			&& is_same(pos->elem, "export")))
		builtin_export(msh, pos);
	else if ((pos->p && pos->p->__token__ == ARG)
		&& is_same(pos->elem, "unset"))
		builtin_unset(msh, pos);
	else if ((!pos->p || (pos->p && pos->p->__token__ == ARG))
		&& is_same(pos->elem, "cd"))
		builtin_cd(msh, pos);
	else
		simple_exec(msh, pos);
}

int	handle_cmd(t_msh *msh, t_cut_cmd *pos)
{
	if (!msh || !pos || !msh->tools->tail)
		return (-1);
	_place_holder_handle_wildcards(msh, pos);
	_place_holder_handle_expand_env(msh, pos);
	write_error(msh);
	msh->tools->tail = pos;
	msh->tools->noforked_exit = 0;
	msh->tools->nbredir = 0;
	msh->tools->is_folder = 0;
	ispipe(msh);
	map_flags(msh, pos, 0, 0);
	whatpostions(msh);
	re_eval_quote(pos);
	if (msh->tools->nbpipe > 0)
		cmd_pipe(msh, pos);
	else
		simple_exec_placeholder(msh, pos);
	move_pos(msh, &pos);
	if ((pos) && (catch_and(msh, &pos) || catch_or(msh, &pos)))
		return (handle_cmd(msh, pos));
	if ((pos) && goto_next_div(msh, &pos))
		return (handle_cmd(msh, pos));
	return (0);
}
