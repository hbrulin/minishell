/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:40:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/20 14:31:42 by hbrulin          ###   ########.fr       */
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
	
	// verif NULL
	//when to free path??
	tab_env = ft_lst_to_tab(env); // must be allocated here for free. !! idk yet where to free. !!
	if ((pid = fork()) == -1)
		return(ft_strerror(NULL, tab_env, "fork", NULL));
	if (pid == 0)
	{
		if((execve(path, args, tab_env)) == -1) // munmap_chunk(): invalid pointer ERROR if fail, why ?
			exit(ft_strerror(NULL, NULL, path, NULL));
		// if fail, valgrind s'affiche puisque execve n'as pas transformer le child minishell en un autre process (a voir)
	}
	else if (pid > 0)
	{
		is_forking(1); 
		if((wpid = wait(&status)) == -1)		// NO NEED TO LOOP, the syscall stops our process till child's end
			return(ft_strerror(path, NULL, "wait", NULL));

		g_ret = WEXITSTATUS(status);
		is_forking(0);
		ft_tabdel((void**)tab_env);
		return (1);
	}
	return (0); 
} 
