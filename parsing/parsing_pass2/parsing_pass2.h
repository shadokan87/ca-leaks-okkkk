/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pass2.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 01:15:35 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 01:15:36 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_PASS2_H
# define PARSING_PASS2_H

# include "../../includes/libshell.h"

int			p_p_ready_to_process(t_msh *msh);

int			p_p_check_par_join(t_msh *msh);

int			p_p_determine_token(t_msh *msh);

t_token		p_p_determine_symbol(char *elem);

t_token		p_p_determine_cmd(char *elem, int cmd_re_eval);

#endif
