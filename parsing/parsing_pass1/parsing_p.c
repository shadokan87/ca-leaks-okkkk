/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 04:42:02 by motoure           #+#    #+#             */
/*   Updated: 2021/09/21 01:19:59 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libshell.h"

char	*p_escape_line(t_msh *msh, char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i])
	{
		if ((is_symbol(str[i])) || (str[i] == '(') || (str[i] == '('))
			i = escape_symbol(msh, str, &ret, i);
		p_putchar_str(&ret, str[i]);
		i++;
	}
	return (ret);
}

static void	replace_args2(t_cut_cmd *cmd, t_cut_cmd **tracer)
{
	t_cut_cmd	*tmp;

	tmp = NULL;
	while (cmd)
	{
		if (is_same(cmd->elem, "<"))
			tmp = cmd->p->p;
		cmd = cmd->p;
	}
	if (tmp)
	{
		if (!tmp->p)
			tmp->n->p = NULL;
		else
			tmp->n->p = tmp->p;
		(*tracer)->n = tmp;
		tmp->p = *tracer;
		tmp->n = NULL;
		*tracer = tmp;
	}
}

static void	replace_args(t_msh *msh, t_cut_cmd *cmd)
{
	t_cut_cmd	**tracer;

	while (cmd && is_same("(", cmd->elem))
		cmd = cmd->p;
	if (!(cmd && is_same("<", cmd->elem)))
		return ;
	if (is_same("(", msh->tools->tail->elem) == 0
		&& is_same(")", msh->tools->tail->elem) == 0)
		tracer = &msh->tools->tail;
	else
	{
		while (msh->tools->tail && (is_same("(", msh->tools->tail->elem)
				|| is_same(")", msh->tools->tail->elem)))
			msh->tools->tail = msh->tools->tail->p;
		tracer = &msh->tools->tail;
	}
	replace_args2(cmd, tracer);
}

void	print_list_way(t_cut_cmd *cmd, char *way)
{
	t_cut_cmd	*iterator;

	iterator = cmd;
	while (iterator)
	{
		if (is_same(way, "p"))
		{
			printf("[%s] -p ", iterator->elem);
			iterator = iterator->p;
		}
		else
		{
			printf("[%s] -n ", iterator->elem);
			iterator = iterator->n;
		}
	}
	printf("\n");
}

int	p_process_line(t_msh *msh)
{
	if (!msh->jobs->have_been_read)
		return (0);
	if (!p_check_quotes(msh))
		return (0);
	if (!msh->tools->head)
	{
		if (!p_check_symbols(msh, msh->jobs->have_been_read)
			|| !p_check_par(msh, msh->jobs->have_been_read))
			return (0);
		msh->jobs->have_been_read
			= p_escape_line(msh, msh->jobs->have_been_read);
		p_str_to_struct(msh, NULL);
	}
	else
		p_p_check_par_join(msh);
	replace_args(msh, msh->tools->tail);
	p_p_determine_token(msh);
	p_p_ready_to_process(msh);
	return ((msh->tools->error_msg == NULL));
}
