/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:12:38 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/03 16:42:15 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	prompt(void)
{
	int status;
	char *input;
	char *trim;
	char **args;

	status = 1;
	input = NULL;
	while(status)
	{
		ft_putstr("minishell > ");
		if (get_next_line(STDIN_FILENO, &input) == -1)
			ft_putstr("Error reading stdin"); //systeme d'erreurs a faire
		//printf("%s\n", input);
		trim = ft_strtrim(input, " "); //autres caracteres a afficher?
		free(input); //on set to NULL en plus?
		args = parser(trim); //FAIRE UN PARSER
		free(trim);
		status = run_dmc(args);
		ft_tabdel((void **)args);
	}
}

int			main(int ac, char **av, char **envp)
{
	(void)ac; 
	(void)av;//comme ca je n'ai que envp
	env = copy_tab(envp);
	prompt();

/*print env var
	int i = 0;
	while(env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
*/
	ft_tabdel((void **)env);
	return(0);
}
