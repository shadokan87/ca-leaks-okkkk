/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redir_in_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 23:57:11 by thhusser          #+#    #+#             */
/*   Updated: 2022/01/18 00:29:56 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_tmp_che(char *tmp, char *str, int *i, int *j)
{
	int		c;

	c = str[*i - 1];
	while (str[*i] != c)
	{
		if ((str[*i] == '>' || str[*i] == '<'))
		{
			if (c == '"')
			{
				tmp[*j] = '\\';
				*j += 1;
			}
			tmp[*j] = '\\';
			*j += 1;
		}
		tmp[*j] = str[*i];
		*j += 1;
		*i += 1;
	}
	return (tmp);
}

int		ft_nbchevron2(const char *str, int i)
{
	if (i == 0)
	{
		if ((str[i] == '>' && ((str[i + 1] != '>' && str[i + 1] != ' ') ||
			(str[i + 1] == '>' && str[i + 2] != ' '))) ||
			(str[i] == '<' && str[i + 1] != ' '))
			return (1);
	}
	else if ((str[i] == '>' && str[i - 1] != '>' && str[i - 1] != ' ' &&
		str[i + 1] != ' ' && str[i + 1] != '>') || (str[i] == '>' &&
		str[i + 1] == '>' && str[i - 1] != ' ' && str[i + 2] != ' ') ||
			(str[i] == '<' && str[i - 1] != ' ' && str[i + 1] != ' '))
		return (2);
	else if ((str[i] == '>' && str[i + 1] != '>' && str[i - 1] != '>' &&
		(str[i - 1] != ' ' || str[i + 1] != ' ')) || (str[i] == '>' &&
		str[i + 1] == '>' && (str[i - 1] != ' ' || str[i + 2] != ' ')) ||
		(str[i] == '<' && (str[i - 1] != ' ' || str[i + 1] != ' ')))
		return (1);
	return (0);
}

int		ft_spacechevron(char *str, int i)
{
	if (((str[i] == '>' && str[i - 1] != ' ' && str[i - 1] != '>' &&
	str[i - 1] != '\\') ||
	(str[i] == '<' && str[i - 1] != ' ' && str[i - 1] != '\\')))
		return (1);
	else if ((str[i - 1] == '>' && str[i] != ' ' && str[i] != '>' &&
	str[i - 2] != '>' && str[i - 2] != '\\')
	|| (str[i - 1] == '<' && str[i] != ' ' && str[i - 2] != '\\') ||
		(str[i - 1] == '>' && str[i] != ' ' && str[i] != '>' &&
		str[i - 2] == '>' && str[i - 3] != '\\'))
		return (1);
	return (0);
}

int		ft_nbchevron(const char *str)
{
	int		i;
	int		nb;
	char	c;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			while (str[i] != c && str[i])
			{
				if (str[i] == '>' || str[i] == '<')
					nb += 2;
				i++;
			}
		}
		nb += ft_nbchevron2(str, i);
		i++;
	}
	return (nb);
}

char	*ft_checkredir2(char *str, char *tmp, int i, int j)
{
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (str[i - 1] == '>' || str[i - 1] == '<')
				tmp[j++] = ' ';
			tmp[j++] = str[i++];
			tmp = get_tmp_che(tmp, str, &i, &j);
		}
		if (i != 0 && str[i] != '"' && str[i] != '\'')
			if (ft_spacechevron(str, i))
				tmp[j++] = ' ';
		tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*ft_checkredir(char *str)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) +
			ft_nbchevron((const char *)str) + 1));
	if (!tmp)
		return (NULL);
	tmp = ft_checkredir2(str, tmp, 0, 0);
	free(str);
	str = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	if (!str)
		return (NULL);
	ft_strcpy(str, tmp);
	free(tmp);
	return (str);
}
