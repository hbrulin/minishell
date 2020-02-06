/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:12:38 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 12:08:40 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

t_env	g_env;

void	prompt(void)
{
	int		status;
	char	*input;
	char	*s;

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

int		main(int ac, char **av, char **envp)
{
	(void)ac; 
	(void)av;
	g_env = copy_tab(envp);
	prompt();
	return(0);
}
