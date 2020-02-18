/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:40:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/18 17:17:45 by pmouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// path && args will not be free in this function anymore

int		ft_execve(char *path, char **args)
{
	pid_t	pid;
	pid_t wpid;
	int status;
	char **tab_env = NULL;
	
	// verif NULL + free if fork fail
	tab_env = ft_lst_to_tab(env); // must be allocated here for free. !! idk yet where to free. !!
	if ((pid = fork()) == -1)
		return(ft_strerror(NULL, NULL, "fork", NULL));
	if (pid == 0)
	{
		if((execve(path, args, tab_env)) == -1) // munmap_chunk(): invalid pointer ERROR if fail, why ?
			exit(ft_strerror(NULL, NULL, path, NULL));
		// if fail, valgrind s'affiche puisque execve n'as pas transformer le child minishell en un autre process (a voir)
	}
	else if (pid > 0)
	{
		g_process_count++;
		if((wpid = wait(&status)) == -1) // NO NEED TO LOOP, the syscall stops our process till child's end
			return(ft_strerror(NULL, NULL, "wait", NULL));
		g_ret = WEXITSTATUS(status);
		g_process_count--;
		ft_tabdel((void**)tab_env);
		return (1); // return(ft_error(NULL, NULL, NULL, NULL));
	}
	return (0); 
} 
