/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:12:38 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/13 20:15:04 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *env = NULL;
t_list *export = NULL;
t_ret	g_ret = 0;
t_ret	exit_ret = 0;

void signal_handler(int n) 
{
	if (is_forking(2) && n == SIGINT)
	{
		ft_putstr("\n");
		g_ret = SIGINT_ERR;
	}
	else if (n == SIGINT)
		g_ret = 1;
	if (is_forking(2) && n == SIGQUIT)
	{
		ft_putstr("Quit: 3\n");
		g_ret = SIGQUIT_ERR;
	}
	else if (n == SIGQUIT)
		g_ret = 0;
}

void	prompt(void)
{
	int		status;
	char	*input;
	char	*s;
	int ret;

	status = 0;
	input = NULL;
	s = NULL;
	while(!status)
	{
		ft_putstr("minishell > ");
		ret = get_next_line(STDIN_FILENO, &input);
		if (ret == 0)
		{
			ft_putstr("exit\n");
			exit(0);
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
	ft_lstclear(&export, free);
	ft_lstclear(&env, free);
	system("leaks minishell");
	return(exit_ret);
}
