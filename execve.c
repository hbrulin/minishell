/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:40:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 16:03:49 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_execve(char **args)
{
	int status;
	status = 1;

	pid_t	pid;
	pid = fork();
	if (pid == 0) //pour dire que je suis dans le processus fils. Quid si erreur de fork?
	{
		if (ft_tablen(args) == 1)
			execve(args[0], NULL, g_env);
		else if (ft_tablen(args) > 1)
			execve(args[0], args + 1, g_env); //controler si parametre passes au programme 
		exit(0);
	}
	wait(&status); //le pere attend le fils pour repartir
	//il faudra prevoir si l'executable n'est pas bon ou permission denied -> check access control
	//OU si command not found
	return (1); //return 1 pour que le shell continue de tourner
} 



