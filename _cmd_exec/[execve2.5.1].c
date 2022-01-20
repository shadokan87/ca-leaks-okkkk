/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [execve2.5.1].c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 00:50:51 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 00:52:45 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

t_token	set_token_as_c(t_token token)
{
	char	token_as_c;

	token_as_c = '0';
	if (token == S_QUOTE)
		token_as_c = '\'';
	else
		token_as_c = '\"';
	return (token_as_c);
}

void	set_exit_status(t_msh *msh, t_cut_cmd *cmd)
{
	char		*tmp;
	t_cut_cmd	*ls;

	if (msh->tools->status == 32512 && !is_builtin(cmd->elem))
	{
		command_not_found(msh, cmd->elem);
		msh->tools->status = 127;
	}
	else if (msh->tools->status == 3584 || msh->tools->status == 3328)
	{
		ls = ft_ls(cmd->elem, NULL);
		msh->tools->to_p = ft_strjoin("minishell: ", cmd->elem);
		if (!ls)
		{
			tmp = ft_strjoin(msh->tools->to_p, ": no such file or directory");
			append_error(msh, NULL, tmp, 127);
		}
		else
		{
			tmp = ft_strjoin(msh->tools->to_p, ": Is a directory");
			append_error(msh, NULL, tmp, 126);
		}
	}
}

char	*del_quotes(char *str, t_token token, int i)
{
	char	to_del;
	char	token_as_c;
	char	*ret;

	ret = NULL;
	to_del = 0;
	if (!str)
		return (str);
	token_as_c = set_token_as_c(token);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			to_del = str[i];
		i++;
	}
	if (to_del == 0 || token_as_c != to_del)
		return (str);
	i = -1;
	while (str[++i])
	{
		if (str[i] != to_del)
			p_putchar_str(&ret, str[i]);
	}
	return (ret);
}
