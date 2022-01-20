/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidminta <tidminta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 01:13:04 by tidminta          #+#    #+#             */
/*   Updated: 2021/09/21 01:13:04 by tidminta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

int	split_len(char **split)
{
	register int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	return (i);
}

char	**list_to_split(t_cut_cmd *target)
{
	char		**ret;
	int			i;
	t_cut_cmd	*count;

	i = 0;
	count = target;
	while (count)
	{
		count = count->n;
		i++;
	}
	ret = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (target)
	{
		ret[i] = ft_strdup(target->elem);
		target = target->n;
		i++;
	}
	return (ret);
}

char	*get_path(t_cut_cmd *cmd, char **paths)
{
	int				i;
	DIR				*o_dir;
	struct dirent	*r_dir;

	i = -1;
	if (!cmd || !paths)
		return (NULL);
	while (paths[++i])
	{
		o_dir = opendir(paths[i]);
		if (o_dir != NULL)
		{
			while (ft_readdir(&r_dir, o_dir))
				if (r_dir && (!ft_strncmp(cmd->elem,
							r_dir->d_name,
							(size_t)ft_strlen(r_dir->d_name))))
					return (ft_strjoin(ft_strjoin(paths[i], "/"), cmd->elem));
			closedir(o_dir);
		}
	}
	return (NULL);
}
