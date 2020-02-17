/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helenebrulin <helenebrulin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:33:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/17 11:30:49 by helenebruli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_pipe(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	parsexec(char *cmd)
{
	int		std_out;
	int		std_in;
	char 	**args;

	std_in = dup(0);
	std_out = dup(1);
	if (!cmd)
		return (0);
	if(!(args = parse_arg(cmd)))
		return (g_ret = ft_error(SYNTAX_ERR, cmd, NULL, NULL));
	free(cmd);
	if (interpreter(args) == 1)
		return (g_ret = ft_error(SYNTAX_ERR, NULL, args, NULL));
	redirect(args);
	if (ft_is_pipe(args))
		run_dmc_pipes(args);
	else
		run_dmc(args); 
	dup2(std_out, 1); //reset les sorties
	dup2(std_in, 0);
	return (g_ret = 0);
}
