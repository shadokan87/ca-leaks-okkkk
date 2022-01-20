/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:02:44 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/09 21:09:58 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

void	catch_and2(t_msh *msh, t_cut_cmd **pos, register int deep)
{
	while (msh->tools->status && (*pos))
	{
		if ((*pos)->__token__ == OPEN_DIV)
			deep++;
		if ((*pos)->__token__ == OR && !deep)
			break ;
		(*pos) = (*pos)->p;
	}
}
