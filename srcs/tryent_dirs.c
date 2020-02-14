// HEADER

#include "minishell.h"

/*
**	Search entry in all the directories specified in 'dirs'
**	dirs must be formatted as follow -> dir1/:/dir2/:/dir3:/dir1/dir2
**	returns the complete path where the entry was found or NULL
**	also returns NULL if dirs or entry is NULL
*/

char	*tryent_dirs(const char *dirs, const char *entry)
{
	int		i;
	int		error;
	char	*dir_path;
	char	c_entry[270];

	if (!dirs || !entry)
		return (NULL);
	c_entry[0] = '/';
	ft_strcpy(&c_entry[1], entry);
	i = -1;
	while (dirs[++i])
	{
		if (dirs[i] == ':')
		{
			dir_path = ft_strnjoin(dirs, c_entry, i);
			dirs += i + 1;							// move pointer to last ':' found
			i = 0;								// reset interator
			if (try_path(dir_path, &error))
				return (dir_path);
			free(dir_path);
		}
	}
	return (NULL);
}
