/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:33:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/28 13:07:59 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_pipe(char **args)
{
	int i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0 && ft_strcmp(args[i - 1], "\\"))
			return (1);
		i++;
	}
	return (0);
}

void	set_io(int i)
{
	static int		std_out;
	static int		std_in;

	if (i == 0)
	{
		std_in = dup(0);
		std_out = dup(1);
	}
	if (i == 1)
	{
		dup2(std_out, 1);
		dup2(std_in, 0);
	}
}

int		ls_part(char **args)
{
	if (ft_tablen(args) >= 2)
	{
		if (!ft_strcmp(args[0], "ls") && (!ft_strcmp(args[1], "\"\"") || !ft_strcmp(args[1], "\'\'")))
		{
			g_ret = 1;
			ft_printf_fd(2, "ls: : No such file or directory\n");
			return(1);
		}
	}
	return (0);
}

int		parsexec(char *cmd)
{
	char	**args;

	set_io(0);
	if (!cmd || !ft_strcmp(cmd, ""))
		return (0);
	if (!(args = parse_args(cmd)))
	{
		g_ret = ESYNTAX;
		return (ft_error(SYNTAX_ERR, cmd, NULL, NULL));
	}
	if (ls_part(args))
	{
		ft_tabdel((void *)args);
		return(0);
	}
	free(cmd);
	if (ft_is_pipe(args))
		run_dmc_pipes(args);
	else
		run_dmc(args);
	ft_tabdel((void *)args);
	return (0);
}
