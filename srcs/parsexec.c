/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:33:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/03/11 21:23:20 by hbrulin          ###   ########.fr       */
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

int		parsexec(char *cmd)
{
	char	**args;
	char	**good_var;

	set_io(0);
	if (!cmd || !ft_strcmp(cmd, ""))
		return (0);
	if (!(args = parse_args(cmd)))
	{
		g_ret = ESYNTAX;
		return (ft_error(SYNTAX_ERR, cmd, NULL, NULL));
	}
	free(cmd);
	if (!(good_var = rm_wrong_var(args)))
		return (ft_ret_errno(NULL, args, NULL));
	ft_tabdel((void *)args);
	if (ft_is_pipe(good_var))
		handle_pipes(good_var);
	else
		run_dmc(good_var);
	ft_tabdel((void *)good_var);
	return (0);
}
