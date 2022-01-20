/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.5.1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:00:05 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 20:00:06 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

static int	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	_error_builtin_exit(t_msh	*msh, t_cut_cmd	*iterator, char **error,
				int *code)
{
	(void)msh;
	(void)error;
	(void)code;
	if (iterator->__token__ == AND
		|| iterator->__token__ == OR
		|| iterator->__token__ == OPEN_DIV
		|| iterator->__token__ == CLOSED_DIV)
		return (0);
	if (!*error && iterator->__token__ != ARG)
	{
		*error = ft_strdup("minishell: exit: usage: exit [exit code]");
		*code = 1;
	}
	if ((!*error && ft_strlen(ft_itoa(ft_atoi(iterator->elem)))
			!= ft_strlen(iterator->elem)) || (!ft_str_isdigit(iterator->elem)))
	{
		*error = ft_strdup("minishell: exit: numeric value required");
		*code = 255;
	}
	return (1);
}

static	void	cut_exit(t_cut_cmd *cmd, t_msh *msh, char *error, int arg_count)
{
	int	code;

	code = msh->tools->status;
	if (arg_count >= 1 && !ft_str_isdigit(cmd->p->elem))
	{
		printf("%s\n", error);
		code = 2;
	}
	else if (arg_count > 1)
	{
		printf("minishell: exit: too many arguments\n");
		msh->tools->status = 1;
		return ;
	}
	else if (error)
		printf("%s\n", error);
	else if (arg_count == 1 && cmd->p->elem)
		code = ft_atoi(cmd->p->elem);
	exit (code);
	gc("collect -all");
}

int	builtin_exit(t_msh *msh, t_cut_cmd *cmd)
{
	int			arg_count;
	int			code;
	char		*error;
	t_cut_cmd	*iterator;

	arg_count = 0;
	code = msh->tools->status;
	iterator = cmd->p;
	error = NULL;
	while (iterator)
	{
		if (!_error_builtin_exit(msh, iterator, &error, &code))
			break ;
		iterator = iterator->p;
		arg_count++;
	}
	cut_exit(cmd, msh, error, arg_count);
	return (2);
}
