//HEADER

#include "minishell.h"

/*
**	!! MAN STAT !! st_mode bit field masks
**	maybe more performant and no need to open dirs
*/

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
