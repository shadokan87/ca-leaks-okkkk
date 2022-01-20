/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 02:50:21 by tidminta          #+#    #+#             */
/*   Updated: 2021/08/31 02:51:09 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H 

# include "../includes/libshell.h"

void	init_jobs(t_msh **msh);

void	init_tools(t_msh *msh);

void	init_msh(t_msh **msh, char **envp);

#endif