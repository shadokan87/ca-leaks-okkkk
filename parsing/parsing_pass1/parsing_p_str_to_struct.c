/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_p_str_to_struct.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 04:41:58 by motoure           #+#    #+#             */
/*   Updated: 2021/09/09 21:18:34 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libshell.h"

static void	case_div(t_msh *msh, char **new, char c)
{
	if (*new)
		add(msh, *new, _UNASSIGNED);
	if (c == '(')
		add(msh, "(", OPEN_DIV);
	else
		add(msh, ")", CLOSED_DIV);
	*new = NULL;
}

static void	p_str_to_struct2(t_msh *msh, char **split)
{
	register int	i;
	register int	z;
	char			*new;

	i = -1;
	z = -1;
	new = NULL;
	while (split[++i])
	{
		while (split[i][++z])
		{
			if ((split[i][z]) && (split[i][z] == '(' || split[i][z] == ')'))
				case_div(msh, &new, split[i][z]);
			else
				p_putchar_str(&new, split[i][z]);
		}
		if (new)
		{
			add(msh, new, _UNASSIGNED);
			new = NULL;
		}
		z = -1;
	}
}

int	p_str_to_struct(t_msh *msh, char *str)
{
	char				**split;

	split = NULL;
	if (!str)
		split = ft_split(msh->jobs->have_been_read, ' ');
	else if (*str != '\"' && *str != '\'')
		split = ft_split(str, ' ');
	if (c_is_present(str, '\"') || c_is_present(str, '\''))
		return (p_quote_to_struct(msh, str));
	p_str_to_struct2(msh, split);
	return (1);
}
