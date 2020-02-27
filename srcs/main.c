/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:12:38 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/27 15:04:35 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*g_env = NULL;
t_list	*g_export = NULL;
t_ret	g_ret = 0;

void	signal_handler(int n)
{
	if (!is_forking(2) && n == SIGINT)
	{
		ft_putstr("\033[1C");
		ft_putstr("\b\b \b\b \b\b");
		ft_putstr("\n");
		ft_putstr("minishell > ");
		g_ret = 1;
	}
	if (!is_forking(2) && n == SIGQUIT)
	{
		ft_putstr("\033[1C");
		ft_putstr("\b\b \b\b \b\b");
		ft_putstr("\033[1C");
		g_ret = 0;
	}
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
		ft_putstr("minishell > ");
		ret = get_next_line(STDIN_FILENO, &input);
		if (ret == 0 && !is_forking(2))
		{
			ft_putstr("exit\n");
			exit(0);
		}
		if (ret == 0 && is_forking(2))
			signal_handler(2);
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
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		ft_strerror(NULL, NULL, "signal", NULL);
		exit(1);
	}
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)
	{
		ft_strerror(NULL, NULL, "signal", NULL);
		exit(1);
	}
	g_env = ft_tab_to_list(&g_env, envp);
	g_export = ft_tab_to_list_custom(&g_export, envp);
	prompt();
	ft_lstclear(&g_export, free);
	ft_lstclear(&g_env, free);
	return (0);
}
