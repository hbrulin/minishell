/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:40:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 17:13:33 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*bin_search(char *cmd)
{
	struct dirent	*bins = NULL;
	DIR				*path_to_bin = NULL;
	char *location = "/bin/";
	path_to_bin = opendir(location);
	if (path_to_bin == NULL)
		return (NULL);
	while ((bins = readdir(path_to_bin)) != NULL)
	{
		if (ft_strcmp(bins->d_name, cmd) == 0)
		{
			closedir(path_to_bin);
			return (ft_strjoin(location, cmd));
		}
		bins++;
	}
	closedir(path_to_bin);
	return (NULL);
}

char *get_path(char **args)
{
	char *path = NULL;

	if ((path = bin_search(args[0])) != NULL)
		return (path);
	else
		return(args[0]);
}

int		ft_execve(char **args)
{
	pid_t	pid;
	char *path = NULL;
	path = get_path(args);
	//ft_putstr(path);
	//ft_putstr("\n");
	pid = fork();
	if (pid == 0)  //Quid si erreur de fork?
	{
		execve(path, args, g_env); 
		exit(0);
	}
	wait(&pid); 
	return (1); 
} 



