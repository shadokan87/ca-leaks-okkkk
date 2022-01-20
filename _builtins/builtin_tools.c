/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:34:58 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/12 05:36:34 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

void	print_wild(t_cut_cmd *wild)
{
	while (wild)
	{
		printf("%s", wild->elem);
		wild = wild->p;
	}
}

void	wild_or_arg(t_cut_cmd *cmd)
{
	if (cmd->__token__ == WILD_CARD)
	{
		printf("wildcard: [%s]\n", cmd->elem);
		exit (0);
	}
	else if ((cmd->p && (cmd->p->__token__ >= ARG && cmd->p->__token__
				<= D_QUOTE && !is_same(cmd->p->elem, "-n"))))
		printf("%s", cmd->p->elem);
}
