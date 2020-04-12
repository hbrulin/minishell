/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:12:43 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/12 17:05:02 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*g_env = NULL;
t_list	*g_export = NULL;
t_ret	g_ret = 0;

void	signal_handler(int n)
{
	if (is_forking(2) == 3)
		ft_putstr("\n");
	else if (!is_forking(2) && n == SIGINT)
	{
		ft_putstr("\n");
		ft_putstr("minishell > ");
		g_ret = 130;
	}
	else if (!is_forking(2) && n == SIGQUIT)
	{
		ft_putstr("\033[1C");
		ft_putstr("\b\b \b\b \b\b");
		ft_putstr("\033[1C");
		g_ret = 0;
	}
}

int		launch(char *input)
{
	char	*s;

	if (!input)
		return (1);
	s = NULL;
	if (!(s = ft_strtrim(input, " ")))
		return (ft_strerror(NULL, NULL, NULL, NULL));
	parse_cmds(s);
	free(s);
	return (0);
}

void	prompt(void)
{
	int		status;
	char	input[ARG_MAX];
	int		ret;

	status = 0;
	while (!status)
	{
		ft_putstr("minishell > ");
		ret = read(STDIN_FILENO, input, ARG_MAX);
		if (ret == ERROR)
			exit(errno);
		if (ret)
		{
			while (input[ret - 1] != '\n')
			{
				ft_putstr("\033[2C\b\b  \033[2D");
				ret += read(STDIN_FILENO, &input[ret], ARG_MAX);
			}
			input[ret - 1] = '\0';
		}
		else
			ft_strlcpy(input, "exit", 5);
		if (launch(input))
			return ;
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
