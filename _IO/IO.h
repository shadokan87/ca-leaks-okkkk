/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IO.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:55:43 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/09 20:11:00 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include "../includes/libshell.h"

int			isredir(t_cut_cmd *cmd);

int			handle_redirection(t_msh *msh, t_cut_cmd *cmd, int fd);

int			is_input(t_cut_cmd **cmd);

int			input_redirection(t_msh *msh, t_cut_cmd *cmd);

int			is_output(t_cut_cmd **cmd);

int			output_redirection(t_msh *msh, t_cut_cmd *cmd);

int			is_div_output(t_cut_cmd **cmd);

int			is_folder(t_msh **msh, char *str);

char		*flag(char *instr);

void		print_list_msg(t_cut_cmd *print, char *message);

t_cut_cmd	*node_match(t_cut_cmd **target, t_cut_cmd *to_find);

#endif
