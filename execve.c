/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:40:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/10 14:43:17 by hbrulin          ###   ########.fr       */
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
		ft_error("minishell: dir /bin/ could not be opened", 0, location, NULL);
		return (NULL);
	}
	while ((bins = readdir(path_to_bin)) != NULL)
	{
		if (ft_strcmp(bins->d_name, cmd) == 0)
		{
			if (closedir(path_to_bin) == -1)
			{
				ft_error("minishell: fatal_error\n", 0, location, NULL);
				exit(EXIT_FAILURE);
			}
			ret = ft_strjoin(location, cmd);
			free(location);
			return (ret);
		}
		bins++;
	}
	if (closedir(path_to_bin) == -1)
	{
		ft_error("minishell: fatal_error\n", 0, location, NULL);
		exit(EXIT_FAILURE);
	}
	return (NULL); 
}

char *get_path(char **args)
{
	char *path;
	
	path = NULL;
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
	char **tab_env = ft_lst_to_tab(env); //A FREE APRES!!!!
	if(!(path = get_path(args)))
		return(ft_error("minishell : error fatal: path was not allocated properly\n", 0, NULL, NULL));
	if(!(ft_access(path)))
		return(ft_error(NULL, 1, path, NULL));
	if ((pid = fork()) == -1)
		return(ft_error("minishell : error fatal: fork was unsuccessful\n", 0, path, NULL));
	if (pid == 0)
	{
		if((execve(path, args, tab_env)) == -1)
			return(ft_error("minishell: %s: command could not be executed\n", 1, path, path));
	}
	else if (pid > 0)
	{
		is_forking(1); //pour signal
		if((wpid = wait(&status)) == -1)
			return(ft_error("minishell : error fatal: wait for child process\n", 0, path, NULL));
		while (wpid != pid)
		{
			if((wpid = wait(&status)) == -1)
				return(ft_error("minishell : error fatal: wait for child process\n", 0, path, NULL));
		}
		if (wpid == pid) //If wait() returns due to a stopped or terminated child process, the process ID of the child is returned to the calling process.
		{
			is_forking(0); //l'enfant est mort, je ne fork plus
			return(ft_error(NULL, 1, path, NULL));
		}
	}
	return (1); 
} 



