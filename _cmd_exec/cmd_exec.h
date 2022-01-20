/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 01:58:22 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 00:52:35 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_EXEC_H
# define CMD_EXEC_H

# define NO_ARGS 0
# define ARGS 1
# define ARGS_BUT 2

# include "../includes/libshell.h"

void		set_exit_status(t_msh *msh, t_cut_cmd *cmd);

void		catch_and2(t_msh *msh, t_cut_cmd **pos, register int deep);

void		init_pos(t_cut_cmd *tail, t_cut_cmd **pos);

void		simple_exec(t_msh *msh, t_cut_cmd *cmd);

void		cmd_nopipe(t_msh *msh, t_cut_cmd *cmd);

void		cmd_pipe(t_msh *msh, t_cut_cmd *cmd);

void		delete_heredoc(t_msh *msh);

void		son_fork(t_msh *msh, t_cut_cmd *cmd, int bfd);

void		father_fork(t_msh *msh, t_cut_cmd *cmd, int pid, int *bfd);

void		move_pos(t_msh *msh, t_cut_cmd **pos);

void		cut_quotes(char *str, char *ret, char to_del);

void		_dollar_handle_append_failure(t_msh *msh,
				t_cut_cmd *iterator, char **current_write, char **elem_ptr);

void		_dollar_append_if_valid(t_msh *msh,
				t_cut_cmd *iterator, char **current_write, char **elem_ptr);

void		_place_holder_handle_expand_env(t_msh *msh, t_cut_cmd *cmd);

void		inc_ret(t_cut_cmd *cmd, int *ret);

char		*del_quotes(char *str, t_token token, int i);

char		*_place_holder_get_path(t_msh *msh, t_cut_cmd *cmd);

char		*determine_path_type(t_cut_cmd *cmd, char *str);

char		*get_val_from_var(t_cut_cmd *var);

char		**handle_heredoc(t_msh *msh, t_cut_cmd *cmd, int mode);

char		**handle_args(t_msh *msh, t_cut_cmd *cmd);

int			choose_args(t_msh *msh);

int			handle_cmd(t_msh *msh, t_cut_cmd *pos);

int			catch_or(t_msh *msh, t_cut_cmd **pos);

int			catch_and(t_msh *msh, t_cut_cmd **pos);

int			strdup_wildcard_or_elem(t_cut_cmd *tail, char ***args, int i);

int			_placeholder_handle_cmd(t_msh *msh);

int			goto_next_div(t_msh *msh, t_cut_cmd **pos);

int			get_dollar_end(char *dollar);

t_token		scope_contain_redir(t_cut_cmd *pos);

t_cut_cmd	*get_next_token_scope(t_cut_cmd *pos, t_token TOKEN);

t_cut_cmd	*is_in_div(t_cut_cmd *pos);

#endif
