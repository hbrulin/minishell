/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:45:04 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/19 18:45:06 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Try to find the given entry in the directories listed in dirs by
**	building an absolute path for each directory.
**	dirs must be formatted as follow -> dir1/:/dir2/:/dir3:/dir1/dir2
**	returns the complete path where the entry was found or NULL
**	also returns NULL if dirs or entry is NULL
*/

char	*build_path(const char *dirs, const char *entry)
{
	int		i;
	char	*dir_path;
	char	c_entry[270];

	if (!dirs || !entry)
		return (NULL);
	errno = 0;
	c_entry[0] = '/';
	ft_strcpy(&c_entry[1], entry);
	i = -1;
	while (dirs[++i])
	{
		if (dirs[i] == ':')
		{
			dir_path = ft_strnjoin(dirs, c_entry, i);
			dirs += i + 1;								// move pointer to last ':' found
			if (try_path(dir_path))
				return (dir_path);
			i = 0;										// reset iterator
			free(dir_path);
		}
	}
	return (NULL);
}
