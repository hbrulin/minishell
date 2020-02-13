/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:40:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/12 15:40:58 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*bin_search(char *cmd)
{
	struct dirent	*bins;
	DIR				*path_to_bin;
	char *location;
	char *ret;
	
	bins = NULL;
	path_to_bin = NULL;
	location = ft_strdup("/bin/");
	ret = NULL;
	if(!(path_to_bin = opendir(location)))
	{
		ft_error(FATAL_ERROR, 0, location, "opendir");
		return (NULL);
	}
	while ((bins = readdir(path_to_bin)) != NULL)
	{
		if (ft_strcmp(bins->d_name, cmd) == 0)
		{
			if (closedir(path_to_bin) == -1)
			{
				ft_error(FATAL_ERROR, 0, location, "closedir");
				exit(EXIT_FAILURE);
			}
			ret = ft_strjoin(location, cmd);
			free(location);
			return (ret);
		}
		bins++;
	}
	if (location)
		free(location);
	if (closedir(path_to_bin) == -1)
	{
		ft_error(FATAL_ERROR, 0, location, "closedir");
		exit(EXIT_FAILURE);
	}
	return (NULL); 
}

char	*try_path(char *path, int *error)
{
	int		i;
	DIR		*dir;
	struct dirent *bin;

	if ((dir = opendir(path)) && closedir(dir) != -1 && (*error = EISDIR))
		return (NULL);
	i = ft_indexr(path, '/');
	path[i] = 0;
	if (!(dir = opendir(path)) && (*error = errno) && (path[i] = '/'))
		return (NULL);
	path[i] = '/';
	*error = !path[i + 1] ? EISDIR : ENOENT;
	while (*error && (bin = readdir(dir)))
		if (!ft_strcmp(bin->d_name, &path[i + 1]))
			*error = 0;
	closedir(dir);
	if (*error)
		return (NULL);
	return (path);
}



