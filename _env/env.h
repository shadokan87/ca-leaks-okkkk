/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 02:37:32 by tidminta          #+#    #+#             */
/*   Updated: 2021/08/31 02:39:23 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../includes/libshell.h"

void		init_envp(t_msh *msh, char **envp);

void		init_env(t_msh *msh, char **envp);

int			add_env(t_msh **msh, char *content, int mode);

int			is_empty_env(t_cut_cmd *env);

int			create_env_list(t_msh **msh, char *content);

int			add_to_env(t_cut_cmd **target, char *elem, t_token TOKEN);

t_cut_cmd	*get_env_of(t_cut_cmd *target, char *to_find);

void		insert_things(t_msh **msh, t_cut_cmd **env_lst,
				t_cut_cmd *new_block);

#endif
