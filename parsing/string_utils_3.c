/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 01:43:07 by motoure           #+#    #+#             */
/*   Updated: 2021/09/21 01:15:39 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

int	get_enum_len(void)
{
	int	i;

	i = _START;
	while (i < _END)
		i++;
	return (i);
}

int	is_same(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2 || ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i])
		return (0);
	return (1);
}

int	get_c_index(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	if (c == '\0')
	{
		while (str[i])
			i++;
		return (i);
	}
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_cwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
		return (ft_strdup(cwd));
	return (NULL);
}

void	print_split(char **split, char *way)
{
	int	i;

	i = 0;
	if (is_same(way, "rev"))
	{
		while (split[i + 1])
			i++;
		while (i > -1)
		{
			ft_putstr_fd(ft_strjoin(split[i], "\n"), 1);
			i--;
		}
	}
	else
	{
		while (split[i])
		{
			ft_putstr_fd(ft_strjoin(split[i], "\n"), 1);
			i++;
		}
	}
}
