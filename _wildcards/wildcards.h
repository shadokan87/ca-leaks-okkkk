/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 20:50:43 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/09 20:52:08 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARDS_H
# define WILDCARDS_H

# include "../includes/libshell.h"

int			match(char *s1, char *s2, char *mode);

t_cut_cmd	**match_end_with(t_msh *msh, char *str);

t_cut_cmd	**match_all(t_msh *msh, char *str);

t_cut_cmd	**match_start_with(t_msh *msh, char *str);

t_cut_cmd	**match_contain(t_msh *msh, char *str);

void		substitute_wildcards_multiple(t_msh *msh, t_cut_cmd **pos);

void		substitute_wildcards(t_msh *msh, t_cut_cmd **pos);

void		_place_holder_handle_wildcards(t_msh *msh, t_cut_cmd *cmd);

void		_place_holder_determine_wildcard_type(t_msh *msh,
				t_cut_cmd **iterator);

#endif
