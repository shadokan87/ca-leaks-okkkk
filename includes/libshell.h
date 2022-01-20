/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libshell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 17:52:06 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/15 03:11:06 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSHELL_H
# define LIBSHELL_H

/*
** La liste des symbols uniques (pour le parsing) (if is_symbol(str[i]) ...)"
*/

# define SYMBOL_LIST ">:<:|:&"
# define SYMBOL_DETERMINE "| > >> < << || && ( )"
# define BUILTIN_LIST "echo cd pwd env export unset exit"

# define SYMBOL_ALLOWED_BEFORE_OPEN_DIV "&&:||:("
# define SYMBOL_ALLOWED_AFTER_CLOSED_DIV "&&:||:):>:>>"

# define W_START_WITH 0
# define W_CONTAIN 1
# define W_END_WITH 2
# define W_ALL 3
# define _DIRECTORY -1

/*
** ERROR_MSG
*/

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <dirent.h>
# include "./struct.h"
# include "./gc.h"
# include "cmd.h"
# include "../_IO/IO.h"
# include "../_IO/pipe/pipe.h"
# include "../_cmd_exec/cmd_exec.h"
# include "../_env/env.h"
# include "../init/init.h"
# include "../error/error.h"
# include "../_builtins/builtins.h"
# include "../parsing/string_utils.h"
# include "../parsing/parsing_pass1/parsing_pass1.h"
# include "../parsing/parsing_pass2/parsing_pass2.h"
# include "../libft/libft.h"
# include "../_wildcards/wildcards.h"
# include <term.h>
# include <termios.h>

t_cut_cmd	**head_tail(t_msh *msh, char *mode);

#endif
