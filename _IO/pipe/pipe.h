/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 20:15:21 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 19:59:58 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "../../includes/libshell.h"

void	ispipe(t_msh *msh);

void	whatpostions(t_msh *msh);

int		getnext_pipe(t_cut_cmd **cmd);

#endif
