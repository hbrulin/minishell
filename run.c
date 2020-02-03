/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:38:26 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/03 16:41:32 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
/*
int		exe(char **args)
{
	fork s utilise si executable, avec execve
	test fork
	pid_t pid;

	//va print deux fois, une fois par processus. Pere id fils, et fils 0.
	pid = fork();
	printf("%i\n", pid);

	exit(0);

	// chercher et lancer le bon executable comme dans bash, base sur une variable d’environnement path ou en utilisant un path absolu 
	//->ici il faudra utiliser ce qui est passe en arg du main

	//vu que cette ft est par defaut, il faudra prevoir si l'executable n'est pas bon

	return (1); //return 1 pour que le shell continue de tourner
} */

int	run_dmc(char **args)
{
	if (!args || !*args || !**args)
		return (1);
	/*if (ft_strcmp(*args, "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(*args, "cd") == 0)
		return (ft_cd(args[1])); //je ne passe que l'option
	else if (ft_strcmp(*args, "pwd") == 0)
		return (ft_pwd(args));
	else if (ft_strcmp(*args, "export") == 0)
		return (ft_export());
	else if (ft_strcmp(*args, "unset") == 0)
		return (ft_unset());
	else if (ft_strcmp(*args, "env") == 0)
		return (ft_env());*/
	if (ft_strncmp(*args, "exit", ft_strlen("exit")) == 0)
		return (0); //set status a 0 et donc quit shell
	//else
	//	return (exe(args)); //si executable passe en param
	return(1);
}
