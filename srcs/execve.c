/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:40:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/14 20:13:47 by hbrulin          ###   ########.fr       */
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

int		ft_execve(char *path, char **args)
{
	pid_t	pid;
	pid_t wpid;
	int status;
	char **tab_env = NULL;
	
	if ((pid = fork()) == -1)
		return(ft_strerror(path, args, "fork", NULL));
	if (pid == 0)
	{
		tab_env = ft_lst_to_tab(env);
		if((execve(path, args, tab_env)) == -1)
		{
			ft_strerror(path, args, path, NULL);
			exit(EXIT_FAILURE);
			return(1);
		}
		ft_tabdel((void *)tab_env);
	}
	else if (pid > 0)
	{
		is_forking(1); 
		if((wpid = wait(&status)) == -1)
			return(ft_strerror(path, args, "wait", NULL));
		while (wpid != pid)
		{
			if((wpid = wait(&status)) == -1)
				return(ft_strerror(path, args, "wait", NULL));
		}
		if (wpid == pid) 
		{
			is_forking(0);
			return(ft_error(NULL, path, args, NULL));
		}
	}
	return (0); 
} 
