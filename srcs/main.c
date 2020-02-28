/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:12:38 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/28 13:14:05 by hbrulin          ###   ########.fr       */
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
	char	input[ARG_MAX];
	char	*s;
	int		ret;

	status = 0;
	s = NULL;
	while (!status)
	{
		ft_putstr("minishell > ");
		ret = read(STDIN_FILENO, input, ARG_MAX);
		if (ret == ERROR)
			exit(errno);
		if (ret)
		{
			if (input[ret - 1] != '\n')
				write(STDOUT_FILENO, "\n", 1);
			else
				input[ret- 1] = '\0';
		}
		else
			ft_strlcpy(input, "exit", 5);
		s = ft_strtrim(input, " ");
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
