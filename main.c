/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:12:38 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/08 17:40:34 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env g_env = NULL;
t_ret g_ret = 0;

void signal_handler(int n) 
{
	//signal(SIGINT, signal_handler); //faire un retour a la ligne
	//signal(SIGQUIT, signal_handler); //afficher infos
	if (is_forking(2) && n == SIGINT) //je passe 2 car je ne veux pas que le statut change
		ft_putstr("\n");
	if (is_forking(2) && n == SIGQUIT)
		ft_putstr("Quit: 3\n");
	(void)n;
}

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
		if (get_next_line(STDIN_FILENO, &input) == 0) //EOF, ctrl D. Prevoir si -1?
		{
			ft_putstr("exit\n");
			exit(0); //free automatiquement
		}
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
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	g_env = copy_tab(envp);
	prompt();
	//ft_printf("%i\n", g_ret);
	return(g_ret);
}
