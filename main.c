/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:12:38 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/03 15:16:11 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

/*
test fork
	pid_t pid;

	//va print deux fois, une fois par processus. Pere id fils, et fils 0.
	pid = fork();
	printf("%i\n", pid);

	exit(0);
*/

void	prompt(void)
{
	int status;
	char *input;

	status = 1;

	while(status)
	{
		ft_putstr("minishell > ");
		if (get_next_line(STDIN_FILENO, &input) == -1)
			ft_putstr("Error reading stdin"); //systeme d'erreurs a faire
		//printf("%s\n", input);
		//recuperer arguments de l'input dans un char **args
		//les executer
		//updater status selon return de l'execution, si c'est un exit status = 1
	}
}

//passer au main **env, qui contient les variables l'environnement (le PATH, l'HOME, l'USER).
int			main(int ac, char **av, char **env)
{
	(void)ac; 
	(void)av;//comme ca je n'ai que de l'env, je passe le PATH, HOME et USER en param??
	env[0][1] = 'b'; //bullshit pour eviter message d'erreur
	prompt();

	return(0);
}
