/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 02:14:36 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/11 19:12:07 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

static char	**heredoc2(t_msh *msh, t_cut_cmd *cmd, t_cut_cmd *tmp)
{
	char		**args;
	int			i;

	i = 0;
	while (tmp != NULL)
	{
		if (tmp != msh->tools->tmp_node && tmp->__token__ != D_L_REDIR)
			i++;
		tmp = tmp->p;
	}
	args = (char **)gc_malloc(sizeof(char *) * i + 1);
	i = -1;
	while (cmd != NULL)
	{
		if (cmd != msh->tools->tmp_node && cmd->__token__ != D_L_REDIR)
			args[++i] = cmd->elem;
		cmd = cmd->p;
	}
	args[++i] = NULL;
	return (args);
}

char	**handle_heredoc(t_msh *msh, t_cut_cmd *cmd, int mode)
{
	t_cut_cmd	*tmp;
	char		**args;

	tmp = cmd;
	if (mode == ARGS)
	{	
		args = (char **)gc_malloc(sizeof(char *) * 3);
		args[0] = ft_strdup(cmd->elem);
		args[1] = ft_strdup("./.msh_heredoc.msh");
		args[2] = NULL;
		msh->tools->istmp = 0;
	}
	else
		args = heredoc2(msh, cmd, tmp);
	return (args);
}

int	choose_args(t_msh *msh)
{
	t_cut_cmd	*cmd;

	cmd = msh->tools->tmp_node;
	if (!msh->tools->istmp)
		return (NO_ARGS);
	else if (cmd->p && cmd->p->__token__ == ARG)
		return (ARGS_BUT);
	else
		return (ARGS);
}

char	**handle_args2(t_cut_cmd *cmd, int i, int ret)
{
	t_cut_cmd	*tail;
	char		**args;

	tail = cmd;
	if (!cmd)
		return (NULL);
	while (cmd && ((cmd->__token__ >= C_BUILTIN
				&& cmd->__token__ <= OPTION) || cmd->__token__ == WILD_CARD))
	{
		inc_ret(cmd, &ret);
		cmd = cmd->p;
	}
	args = ft_calloc((ret + 1), sizeof(char *) * (ret + 1));
	while (tail && ((tail->__token__ >= C_BUILTIN
				&& tail->__token__ <= OPTION) || tail->__token__ == WILD_CARD))
	{
		ret = strdup_wildcard_or_elem(tail, &args, i);
		tail = tail->p;
		i += ret;
	}
	args[i] = NULL;
	return (args);
}

char	**handle_args(t_msh *msh, t_cut_cmd *cmd)
{
	int		ret;
	int		i;
	int		tmp_check;
	char	**args;

	i = 0;
	ret = 0;
	if (!msh || !cmd)
		return (NULL);
	tmp_check = choose_args(msh);
	if (msh->tools->istmp && (tmp_check == ARGS || tmp_check == ARGS_BUT))
		args = handle_heredoc(msh, cmd, tmp_check);
	else
		args = handle_args2(cmd, i, ret);
	return (args);
}
