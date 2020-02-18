/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helenebrulin <helenebrulin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:12:38 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/18 16:37:14 by pmouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*env = NULL;
t_list	*export = NULL;
t_ret	g_ret = 0;
int	g_process_count = 0;

void	signal_handler(int n) 
{
	// CTRL-C when doing nothing should diplay a new prompt
	if (g_process_count > 0 && n == SIGINT)
	{
		ft_putstr("\n");
		g_ret = SIGINT_ERR;
	}
	else if (n == SIGINT)
		g_ret = 1;
	if (g_process_count > 0 && n == SIGQUIT)
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
	int		ret;

	status = 0;
	input = NULL;
	s = NULL;
	while (!status)
	{
		if (isatty(1)) // COLOR PROMPT
			ft_putstr("\e[38;2;0;255;10m");
		ft_putstr("minishell > ");
		if (isatty(1))
			ft_putstr("\e[0m");
		ret = get_next_line(STDIN_FILENO, &input);
		if (ret == 0)
		{
			ft_putstr("exit\n");
			exit(0);
		}
		s = ft_strtrim(input, " ");
		free(input);
		parse_cmds(s);
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
	return (0);
}
