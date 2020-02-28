/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:33:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/28 14:46:23 by hbrulin          ###   ########.fr       */
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
	int i = 0;
	int j;
	char *tmp;

	if (ft_tablen(args) < 2)
		return (0);
	if ((!ft_strcmp(args[1], "\"\"") || !ft_strcmp(args[1], "\'\'")) && !args[2])
	{
		g_ret = 1;
		ft_printf_fd(2, "ls: : No such file or directory\n");
		return (1);
	}
	else if (args[1][0] == '\"' && args[1][1] == '$')
	{
			j = 0;
			tmp = ft_strdup(args[i]);
			while (args[i][j] != '\"' && args[i][j])
				j++;
			tmp[j] = '=';
			if (!get_var(g_env, tmp))
			{
				g_ret = 1;
				ft_printf_fd(2, "ls: : No such file or directory\n");
				return (ft_error(NULL, tmp, NULL, NULL));
			}
			free(tmp);
	}
	while (args[i])
	{
		if (!ft_strcmp(args[i], "\"\"") || !ft_strcmp(args[i], "\'\'"))
		{
			g_ret = 1;
			ft_printf_fd(2, "ls: : No such file or directory\n");
		}
		else if (args[i][0] == '\"' && args[i][1] == '$')
		{
			j = 0;
			tmp = ft_strdup(args[i]);
			while (args[i][j] != '\"' && args[i][j])
				j++;
			tmp[j] = '=';
			if (!get_var(g_env, tmp))
			{
				g_ret = 1;
				ft_printf_fd(2, "ls: : No such file or directory\n");
			}
			free(tmp);
		}
		i++;
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
	/*if (!ft_strcmp(args[0], "ls"))
	{
		if(ls_part(args))
		{
			ft_tabdel((void *)args);
			return(0);
		}
	}*/
	free(cmd);
	if (ft_is_pipe(args))
		run_dmc_pipes(args);
	else
		run_dmc(args);
	ft_tabdel((void *)args);
	return (0);
}
