/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:02:57 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 00:37:20 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../includes/libshell.h"

# define EXPORT 0
# define UNSET 1

int			builtin_export(t_msh *msh, t_cut_cmd *cmd);

int			builtin_unset(t_msh *msh, t_cut_cmd *cmd);

int			builtin_exit(t_msh *msh, t_cut_cmd *cmd);

void		add_builtin(int (***f_p_builtin)(t_msh *msh,
					t_cut_cmd *cmd), void *addr, int size);

void		handle_builtins(t_msh *msh, t_cut_cmd *cmd);

int			builtin_echo_return_value(t_msh *msh, t_cut_cmd *cmd, int mode);

int			builtin_echo(t_msh *msh, t_cut_cmd *cmd);

int			builtin_cd(t_msh *msh, t_cut_cmd *cmd);

int			builtin_pwd(t_msh *msh, t_cut_cmd *cmd);

int			builtin_env(t_msh *msh, t_cut_cmd *cmd);

int			cut_option(t_msh *msh, t_cut_cmd *cmd);

void		cut_echo(t_msh *msh, t_cut_cmd *cmd, char *mode);

int			print_env(t_msh *msh, t_cut_cmd *target);

int			swap_env(t_msh **msh, char *new);

int			check_o(t_msh *msh, t_cut_cmd *cmd);

int			check_e(t_msh *msh, t_cut_cmd *cmd, char *str, int mode);

int			print_export(t_msh *msh, t_cut_cmd *env,
				char **env_split, char *to_print);

int			is_env(t_msh **msh, char *to_pop);

int			ft_readdir(struct dirent **de, DIR *dr);

int			_error_builtin_exit(t_msh	*msh, t_cut_cmd	*iterator, char **error,
				int *code);

void		print_alpha_export(t_msh *msh, t_cut_cmd *cmd);

void		ft_open(int *ret, int fd);

char		*flag(char *instr);

void		flag_loop(char *loop);

char		*flag_cmp(t_cut_cmd *flags, char *instr);

void		print_list_msg(t_cut_cmd *print, char *message);

void		pop_env(t_msh **msh);

void		echo_print_wildcard(t_cut_cmd *wild, t_cut_cmd *iterator);

void		builtins_cut(t_msh *msh, t_cut_cmd *cmd,
				int (**f_p_builtin)(t_msh *msh, t_cut_cmd *cmd));

t_cut_cmd	*bubble_sort(t_cut_cmd *cmd);

t_cut_cmd	*ft_ls(char *path, char *options);

#endif
