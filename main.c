/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:12:38 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/11 17:07:27 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *env = NULL;
t_list *export = NULL;
t_ret	g_ret = 0;

void signal_handler(int n) 
{
	if (is_forking(2) && n == SIGINT)
		ft_putstr("\n");
	if (is_forking(2) && n == SIGQUIT)
		ft_putstr("Quit: 3\n");
}

void	prompt(void)
{
	int		status;
	char	*input;
	char	*s;
	int ret;

	status = 1;
	input = NULL;
	s = NULL;
	while(status)
	{
		ft_putstr("minishell > ");
		ret = get_next_line(STDIN_FILENO, &input);
		if (ret == 0) //EOF, ctrl D. Prevoir si -1?
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
	env = ft_tab_to_list(&env, envp);
	export = ft_tab_to_list_custom(&export, envp);
	prompt();
	//ft_lstclear(&export, free);
	//ft_lstclear(&env, free);
	system("leaks minishell");
	return(g_ret);
}
