/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:12:38 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/05 17:55:12 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	prompt(void)
{
	int status;
	char *input;
	char *s;

	status = 1;
	input = NULL;
	while(status)
	{
		ft_putstr("minishell > ");
		if (get_next_line(STDIN_FILENO, &input) == -1)
			ft_putstr("Error reading stdin");
		s = ft_strtrim(input, " ");
		free(input);
		status = run(s);
		free(s);
	}
}

int			main(int ac, char **av, char **envp)
{
	(void)ac; 
	(void)av;
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
