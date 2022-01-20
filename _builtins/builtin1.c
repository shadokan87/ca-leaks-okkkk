/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 23:55:15 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 00:35:27 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

int	builtin_export(t_msh *msh, t_cut_cmd *cmd)
{
	char	**env_split;

	env_split = NULL;
	if (!msh || !cmd)
		exit (0);
	if ((!cmd->p) || ((cmd->p)
			&& ((cmd->p->__token__ >= PIPE && cmd->p->__token__ <= D_L_REDIR)
				|| cmd->p->elem[0] == '#')))
	{
		return (print_export(msh, msh->env->head, env_split, msh->tools->to_p));
	}
	cmd = cmd->p;
	while (cmd && (!(cmd->__token__ >= PIPE && cmd->__token__ <= CLOSED_DIV)))
	{
		if (cmd->__token__ >= ARG && cmd->__token__ <= D_QUOTE
			&& (check_o(msh, cmd) == SUCCESS
				&& check_e(msh, cmd, cmd->elem, EXPORT) == SUCCESS))
			swap_env(&msh, cmd->elem);
		cmd = cmd->p;
	}
	return (SUCCESS);
}

int	builtin_unset(t_msh *msh, t_cut_cmd *cmd)
{
	if (!msh || !cmd)
		return (0);
	cmd = cmd->p;
	msh->tools->status = 0;
	if (cmd->elem[0] == '$')
		return (check_e(msh, cmd, cmd->elem, UNSET));
	while (cmd && (cmd->__token__ == ARG))
	{
		if (is_env(&msh, cmd->elem) == SUCCESS)
			pop_env(&msh);
		cmd = cmd->p;
	}
	return (2);
}

int	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

void	add_builtin(int (***f_p_builtin)(t_msh *msh, t_cut_cmd *cmd),
		void *addr, int size)
{
	static int	pos;
	char		*add_fail;

	add_fail = ft_strdup("BUILTIN_ARRAY_OVERFLOW, exiting now\n");
	(void)f_p_builtin;
	if (pos == size)
	{
		write(2, add_fail, ft_strlen(add_fail));
		gc("collect -all");
		exit (0);
	}
	(*f_p_builtin)[pos] = addr;
	pos++;
}

void	handle_builtins(t_msh *msh, t_cut_cmd *cmd)
{
	static int	(**f_p_builtin)(t_msh *msh, t_cut_cmd *cmd);
	int			(*malloc_size)(t_msh *msh, t_cut_cmd *cmd);
	int			size;

	size = split_len(ft_split(BUILTIN_LIST, ' '));
	if (!f_p_builtin)
	{
		gc("pause");
		f_p_builtin = ft_calloc(size, sizeof(malloc_size) * size);
		gc("resume");
		add_builtin(&f_p_builtin, builtin_echo, size);
		add_builtin(&f_p_builtin, builtin_cd, size);
		add_builtin(&f_p_builtin, builtin_pwd, size);
		add_builtin(&f_p_builtin, builtin_env, size);
		add_builtin(&f_p_builtin, builtin_export, size);
		add_builtin(&f_p_builtin, builtin_unset, size);
		add_builtin(&f_p_builtin, builtin_exit, size);
	}
	builtins_cut(msh, cmd, f_p_builtin);
	exit (msh->tools->status);
}
