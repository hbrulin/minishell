/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 09:57:33 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/28 16:02:48 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Dans path_exec : trypath : a complete path was given / path absolu, we only
**	want to check it, errors will be : ENOENT, EISDIR, ENOTDIR.
**	OR if a command name was given, we'll try to build paths from $PATH var,
**	error will be custom : 'command not found'
**	Build_path : Try to find the given entry in the directories listed in dirs
**	by building an absolute path for each directory.
**	dirs must be formatted as follow -> dir1/:/dir2/:/dir3:/dir1/dir2
**	returns the complete path where the entry was found or NULL
**	also returns NULL if dirs or entry is NULL
*/

char	*try_path(char *path)
{
	struct stat	file;

	errno = 0;
	stat(path, &file);
	if (errno)
		return (NULL);
	if ((file.st_mode & S_IFMT) == S_IFDIR && (errno = EISDIR))
		return (NULL);
	return (path);
}

char	*no_colon(const char *dirs, char *c_entry)
{
	char	*dir_path;

	if (!(dir_path = ft_strjoin(dirs, c_entry)))
		return (NULL);
	if (try_path(dir_path))
		return (dir_path);
	g_ret = 127;
	free(dir_path);
	return (NULL);
}

void	set_c_entry(char *c_entry, const char *entry)
{
	c_entry[0] = '/';
	ft_strcpy(&c_entry[1], entry);
}

char	*build_path(const char *dirs, const char *entry)
{
	int		i;
	char	*dir_path;
	char	c_entry[270];

	if (!dirs || !entry)
		return (NULL);
	set_c_entry(c_entry, entry);
	i = -1;
	if (!(ft_strchr(dirs, ':')))
		return (no_colon(dirs, c_entry));
	while (dirs[++i])
	{
		if (dirs[i] == ':')
		{
			if (!(dir_path = ft_strnjoin(dirs, c_entry, i)))
				return (NULL);
			dirs += i + 1;
			if (try_path(dir_path))
				return (dir_path);
			i = 0;
			free(dir_path);
		}
	}
	g_ret = 127;
	return (NULL);
}
