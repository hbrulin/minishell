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
	int i;
	int error;
	char *dir_path;

	if (!dirs || !entry)
		return (NULL);
	i = ft_strlen(dirs);
	while (dirs && dirs[--i]) // this was for progrssively puts \0 but bad solution
	{
		if (dirs[i] == ':')
		{
			// construct path en try it
		}
	}
	return (NULL);
}
