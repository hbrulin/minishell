/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:40:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/08 16:02:50 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_forking(int val)
{
	static int is_forking = 0;

	if (val != 2)
		is_forking = val;
	return (is_forking);
}

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
	closedir(path_to_bin); //quid si error? opendir et closedir utilisent errno. faire sortie d'erreurs?
	return (NULL); 
}

char *get_path(char **args)
{
	char *path = NULL;

	if ((path = bin_search(args[0])) != NULL)
		return (path);
	else
		path = ft_strdup(args[0]);
	return(path);
}

int		ft_execve(char **args)
{
	pid_t	pid;
	pid_t wpid;
	int status;
	char *path = NULL;
	path = get_path(args);
	if(!(ft_access(path)))
		return(1);
	if ((pid = fork()) == -1)
		return (1); // avec erreur msg
	if (pid == 0)  //Quid si erreur de fork?
			execve(path, args, g_env);
	else if (pid > 0)//je suis dans le pere
	{
		is_forking(1); //pour signal
		wpid = wait(&status);
		while (wpid != pid)
			wpid = wait(&status);
		if (wpid == pid) //If wait() returns due to a stopped or terminated child process, the process ID of the child is returned to the calling process.
		{
			is_forking(0); //l'enfant est mort, je ne fork plus
			free(path);
			return(1);
		}
	}
	return (1); 
} 



