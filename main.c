/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:12:38 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 16:41:20 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env g_env = NULL;
t_ret g_ret = 0;

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
		status = parse_cmds(s);
		free(s);
	}
}

int		main(int ac, char **av, char **envp)
{
	(void)ac; 
	(void)av;
	g_env = copy_tab(envp);
	prompt();
	//ft_printf("%i\n", g_ret);
	return(g_ret);
}
