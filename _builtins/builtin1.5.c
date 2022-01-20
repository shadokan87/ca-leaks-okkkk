/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 23:54:14 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 00:55:59 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

int	cut_option(t_msh *msh, t_cut_cmd *cmd)
{
	char	*tmp;
	char	*str;

	tmp = NULL;
	str = NULL;
	msh->tools->noforked_exit = 1;
	tmp = ft_substr(cmd->elem, 0, 2);
	str = ft_strdup("bash: export: ");
	str = ft_strjoin(str, tmp);
	str = ft_strjoin(str, ": invalid option\nexport: ");
	str = ft_strjoin(str, "usage: export [no option] [name[=value] ...]");
	append_error(msh, cmd, str, 2);
	return (ERROR);
}

int	check_o(t_msh *msh, t_cut_cmd *cmd)
{
	int		quote;

	quote = 0;
	while (cmd && (cmd->__token__ == ARG
			|| cmd->__token__ == OPTION || cmd->__token__ == D_QUOTE
			|| cmd->__token__ == S_QUOTE))
	{
		if (cmd->__token__ == D_QUOTE || cmd->__token__ == S_QUOTE)
			quote = 1;
		if (cmd->elem[quote] == '-')
		{
			cut_option(msh, cmd);
			return (ERROR);
		}
		quote = 0;
		cmd = cmd->p;
	}
	return (SUCCESS);
}

int	check_e(t_msh *msh, t_cut_cmd *cmd, char *str, int mode)
{
	char	*error;
	int		i;

	error = NULL;
	i = 0;
	(void)cmd;
	if (flag("EXPORT_NONSTRICT == true"))
		return (SUCCESS);
	if ((!ft_isalpha(str[0]) && str[0] != ' ')
		&& (str[i] != '_' || str[i] != '\\'))
	{
		if (mode == EXPORT)
			error = ft_strdup("minishell: export: \'");
		else
			error = ft_strdup("minishell: unset: \'");
		error = ft_strjoin(error, str);
		error = ft_strjoin(error, "\': not a valid identifier");
		msh->tools->noforked_exit = 1;
		append_error(msh, cmd, error, 1);
		return (ERROR);
	}
	return (SUCCESS);
}

void	pop_env(t_msh **msh)
{
	t_cut_cmd	*to_pop;

	if (!(*msh))
		return ;
	to_pop = (*msh)->tools->tmp_node;
	if (!to_pop->n || to_pop->n == NULL)
	{
		to_pop->p->n = NULL;
		(*msh)->env->tail = to_pop->p;
	}
	else if (!to_pop->p || to_pop->p == NULL)
	{
		to_pop->n->p = NULL;
		(*msh)->env->head = to_pop->n;
	}
	else
	{
		to_pop->p->n = to_pop->n;
		to_pop->n->p = to_pop->p;
	}
}
