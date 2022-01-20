/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 17:33:58 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 20:05:32 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "./libshell.h"

typedef enum __token__
{
	_START,
	_UNASSIGNED,
	C_BUILTIN,
	C_ENV,
	LAST_CMD,
	ARG,
	OPTION,
	S_QUOTE,
	D_QUOTE,
	WILD_CARD,
	ENV_SOLO,
	PIPE,
	R_REDIR,
	D_R_REDIR,
	L_REDIR,
	D_L_REDIR,
	OR,
	AND,
	OPEN_DIV,
	CLOSED_DIV,
	_END,
}	t_token;

typedef struct s_jobs
{
	char	*reading_line;
	char	*have_been_read;
	int		prompt_status;
}			t_job;

typedef struct s_cut_cmd
{
	t_token				__token__;
	char				*elem;
	int					is_last;
	int					wild_card_type;
	int					fd_flag;
	int					pid;
	struct s_cut_cmd	*n;
	struct s_cut_cmd	*p;
	struct s_cut_cmd	*tail_wild_card;
	struct s_cut_cmd	*head_wild_card;
}						t_cut_cmd;

typedef struct s_env_list
{
	struct s_cut_cmd	*tail;
	struct s_cut_cmd	*head;
	struct s_cut_cmd	*sub;
	int					size;
}						t_env_list;

typedef struct s_pid_list
{
	int					size;
	struct s_cut_cmd	*tail;
	struct s_cut_cmd	*head;
}					t_pid_list;

typedef struct s_tools
{
	t_cut_cmd	*errors;
	t_cut_cmd	*head;
	t_cut_cmd	*tail;
	t_cut_cmd	*tmp_node;
	t_cut_cmd	**flag_map;
	t_pid_list	*w_pids;
	int			b_stdout;
	int			fdin;
	int			fdout;
	int			tmpfd;
	int			nbpipe;
	int			nbredir;
	int			istmp;
	int			last_op;
	int			status;
	int			run_status;
	int			tmp_status;
	int			pipe[2];
	int			noforked_exit;
	int			history_fd;
	int			echo_opt;
	int			is_folder;
	char		*error_msg;
	char		*marker;
	char		*to_p;

}				t_tools;

typedef struct s_msh
{
	t_job		*jobs;
	t_cut_cmd	*line;
	t_cut_cmd	*envp;
	t_env_list	*env;
	char		**path;
	t_tools		*tools;
}				t_msh;

#endif
