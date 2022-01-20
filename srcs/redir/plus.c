#include "../includes/minishell.h"

void print_2Dtab(char** tab, char *str)
{
	int i = 0;
	while(tab[i])
    	{
		printf("%s[%d]: %s\n", str, i, tab[i]);
		i++;
    	}
}

char **get_file(char *str)
{
    char **out_file;
	//not simple split
    out_file = ft_split(str, '>');
	return (out_file);
}

char *get_pwd()
{
    char buf[1024];
	char *cwd;

	cwd = getcwd(buf, sizeof(buf));
    return(cwd);
}

char **get_argv_redir(char *cmd)
{
	char			**tab;
	char			**argv;
	int	i;
	int	argc;

	i = 0;
	argc = 1;
	tab = creat_list_arg(cmd);
	while (tab[i] && tab[i+1])
	{
		if (ft_strequ(tab[i+1], ">") || ft_strequ(tab[i+1], ">>"))
		{
			//TODO: other descriptor ...
			if (ft_strequ(tab[i], "1") || ft_strequ(tab[i], "2") || ft_strequ(tab[i], "&"))
				argc = i;
			else
				argc = i + 1;
			break;
		}
		else if (ft_strequ(tab[i+1], "<") || ft_strequ(tab[i+1], "<<"))
		{
			argc = i + 1;
			break;
		}
		i++;
		argc++;
	}
	argv = (char **)malloc(sizeof(char *) * (argc + 1));
	argv[argc] = NULL;
	i = 0;
	while (i < argc)
	{
		argv[i] = ft_strdup(tab[i]);
		i++;
	}
	free_split(tab);
	return (argv);
}

char **get_env_tab(t_list *env)
{
	t_list *l;
	char **ret;
	int i;

	ret = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	i = 0;
	l = env;
	while (l)
	{
		ret[i++] = ft_strdup((char*)(l->content));
		l = l->next;
	}
	ret[i] = NULL;
	return (ret);
}

int get_redir_in_file(char *cmd)
{
	char  **tab;
	int i;
	int fd;

	fd = 0;
	
	//free(cmd);
	//cmd = ft_strdup("cat << d > file_out");
	//printf("what cmd: %s\n", cmd);
	
	tab = creat_list_arg(cmd);
	//print_2Dtab(tab, "cmd tab");
	i = 0;
	while (tab[i] && tab[i + 1])
	{
        if (ft_strequ(tab[i], "<") && !ft_strequ(tab[i+1], "<"))
		{
			if (fd > 0)
				close(fd);
			fd = open(tab[i + 1], O_RDONLY);
			if (fd < 0)
			{
				error_out2(NULL, tab[i + 1], "No such file or directory");
				exit_free(tab);
				g_ms->ret_errno = 1;
				return (-1);
			}
			//printf("redir < :fd: %d\n", fd);
		}
        	else if (ft_strequ(tab[i], "<") && ft_strequ(tab[i+1], "<") && tab[i + 2]) // "<<"
		{
			if (fd > 0)
				close(fd);
			char *delimitor = tab[i + 2]; //TDDO: delimitor quote ?
			//fd = open("redir_lessless", O_CREAT | O_EXCL | O_RDWR | O_APPEND, 0644);
			fd = open("redir_lessless", O_CREAT | O_WRONLY | O_APPEND | O_TRUNC, 0644);
			while (1)
			{
				char *s = readline("> ");
				//printf("readline s: %s\n", s);
				if (ft_strequ(s, delimitor))
					break;
				ft_putstr_fd(s, fd);
				ft_putstr_fd("\n", fd);
			}
			close(fd);
			fd = open("redir_lessless", O_RDONLY);//TODO:unlink file
			//printf("redir << :fd: %d\n", fd);
			i++;
		}
		i++;
	}
	free_split(tab);
	return (fd);
}
int get_redir_out_file(char *cmd)
{
	char  **tab;
	int i;
	int fd;
	int is_double;
	char *redir_file;

	redir_file = NULL;
	is_double = 0;
	tab = creat_list_arg(cmd);
	i = 0;
	while (tab[i] && tab[i + 1])
	{
		//find file name after > >>
        	if (ft_strequ(tab[i], ">"))
		{
			fd = open(tab[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
			//printf("redir > :fd: %d\n", fd);
			close(fd);
			if (redir_file)
				free(redir_file);
			redir_file = ft_strdup(tab[i + 1]);
		}
        	else if (ft_strequ(tab[i], ">>"))
		{
			fd = open(tab[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0664);
			//printf("redir >> :fd: %d\n", fd);
			close(fd);
			if (redir_file)
				free(redir_file);
			redir_file = ft_strdup(tab[i + 1]);
			is_double = 1;
		}
		i++;
	}
	free_split(tab);
	//printf("redir out: %s\n", redir_file);
	if (!redir_file)
		return (0);
	if (is_double == 0)
		fd = open(redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else
		fd = open(redir_file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	free(redir_file);
	return (fd);
}

