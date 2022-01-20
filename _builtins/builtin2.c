/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:01:42 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 00:37:47 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

int	set_endl(t_cut_cmd *iterator, t_cut_cmd **case_move)
{
	int	endl;
	int	i;

	endl = 1;
	i = 0;
	if (iterator && iterator->__token__ == OPTION)
	{
		while (iterator->elem[i] && iterator->elem[i] == '-')
			i++;
		if (iterator->elem[i] && iterator->elem[i] == 'n')
		{
			endl = 0;
			(*case_move) = (*case_move)->p;
		}
	}
	return (endl);
}

int	builtin_echo(t_msh *msh, t_cut_cmd *cmd)
{
	t_cut_cmd	*iterator;
	int			endl;

	endl = 1;
	iterator = cmd->p;
	endl = set_endl(iterator, &iterator);
	while (iterator && iterator->__token__ >= C_BUILTIN
		&& iterator->__token__ <= WILD_CARD)
	{
		if (!iterator->elem)
			iterator->elem = ft_strdup("");
		if (iterator->tail_wild_card)
			echo_print_wildcard(iterator->tail_wild_card, iterator);
		if (iterator->p && !iterator->tail_wild_card)
			printf("%s ", iterator->elem);
		else if (iterator->__token__ && !iterator->tail_wild_card)
			printf("%s", iterator->elem);
		iterator = iterator->p;
	}
	if (endl)
		printf("\n");
	msh->tools->status = 0;
	return (1);
}

int	builtin_cd(t_msh *msh, t_cut_cmd *cmd)
{
	char	*str;
	char	*tmp;
	char	*tmp2;

	if ((!cmd->p) || (is_same(cmd->p->elem, "~") && !cmd->p->p))
	{
		str = get_val_from_var(get_env_of(msh->env->head, "HOME"));
		if (!str)
			return (append_error(msh, cmd, "HOME not set\n", 1));
		msh->tools->status = chdir((const char *)str);
		return (msh->tools->status);
	}
	else if ((!((cmd->p->__token__ >= ARG) && (cmd->p->__token__ <= D_QUOTE))))
		return (append_error(msh, cmd, "cd: usage: [path]\n", 1));
	msh->tools->status = chdir((const char *)cmd->p->elem);
	if (msh->tools->status == -1)
	{
		tmp = ft_strjoin("Minishell: cd: ", cmd->p->elem);
		tmp2 = ft_strjoin(tmp, ": No such file or directory");
		return (append_error(msh, cmd, tmp2, 1));
	}
	return (0);
}

int	builtin_pwd(t_msh *msh, t_cut_cmd *cmd)
{
	char	*pwd;

	(void)cmd;
	pwd = get_cwd();
	msh->tools->status = 0;
	if (pwd)
		printf("%s\n", pwd);
	else
		msh->tools->status = 1;
	return (1);
}

int	builtin_env(t_msh *msh, t_cut_cmd *cmd)
{
	if (cmd->p && (cmd->p->__token__ == ARG || cmd->p->__token__ == OPTION))
		return ((msh->tools->status = 0));
	return (print_env(msh, msh->env->head));
}
