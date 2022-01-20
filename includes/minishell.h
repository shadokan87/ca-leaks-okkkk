/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:24:56 by thhusser          #+#    #+#             */
/*   Updated: 2022/01/16 23:56:05 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
// # include "signal.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# include <sys/wait.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>


# define PATH_MAX_ENV 4096
# define DEBUG 0

typedef struct 	s_ms
{
				int 	ret;
				char 	*ret_dir;
				pid_t		pid[2];
				int			last_cmd;
				int 		nb_cmd_pipe;
				char 	*line;
				t_list	*env;
				char	**path;
				char 	**cmd_tab;
				int 	cmd_ac;
				t_list	*cmd;
				t_list	*cmd_tmp;
				t_list	*error;
				int	ret_errno;
				int exit;
}				t_ms;

t_ms			*g_ms = NULL;

void		ft_exit_plus(char **cmd);

//echo $
char	*check_var_cmd(t_ms *g, char *cmd);
// int		takepath(char *str, int idx, char *tmp, t_ms *g);

//doucle char
char	**creat_list_arg(char *line);
void print_split(char **cmd);//tmp

//pipe
void    pipe_command(t_ms *g, int pipe);
void	init_pipe(t_ms *g);

//utils pipe
int		move_space_after(char *str, int i);
int		move_space_before(char *str, int c);

//list
void	record_list(t_list **list, char *str);
void	print_list(t_list *error);

//free and exit
void	ft_exit(int nb, t_ms *g, int ret, char *line);
void	free_split(char **split);

//utils parsing check
int		parseur_quotes(t_ms *g, int i, int c);
int		parseur_quotes_str(char *str, int i, int c);
int		parsing_redirection_out(int i, int res, t_ms *g);
int		parsing_redirection_in(int i, int res, t_ms *g);
int		parsing_pipe(int i, int res, t_ms *g);
int		parse_error(int res, char *erreur, t_ms *g);

//clean redir
char	*get_tmp_che(char *tmp, char *str, int *i, int *j);
int		ft_nbchevron2(const char *str, int i);
int		ft_spacechevron(char *str, int i);
int		ft_nbchevron(const char *str);
char	*ft_checkredir2(char *str, char *tmp, int i, int j);
char	*ft_checkredir(char *str);

void	get_path(t_ms *g);
char	*get_cmd_in_line_th(char *line, t_ms *g);
int		find_cmd_path(char *cmd, t_ms *g);
void	init_global_struct(t_ms *g);
void	record_list(t_list **list, char *str);
void	print_list(t_list *error);
void ft_echo(t_ms *g);
void ft_export(char *cmd, t_ms *g);
void ft_cd(t_ms *g);
void ft_pwd(t_ms *g);
void ft_unset(t_ms *g);
void	exit_free(char **str);
t_list	*ft_lst_pop_last(t_list **lst);
char* get_env(char *str, t_list *env);
int get_cmd_size(char *cmd);
int		check_uset_error(char *str);
char *get_pwd();

//redir fonctions
int ft_output(char *comd, char *direct, t_ms *g);
char **get_file(char *str);
int get_redir_out_file(char *cmd);
char **get_argv_redir(char *cmd);
void print_2Dtab(char** tab, char *str);
int get_redir_in_file(char *cmd);
void error_out2(char *comd, char *opt, char *msg);
char **get_env_tab(t_list *env);
#endif
