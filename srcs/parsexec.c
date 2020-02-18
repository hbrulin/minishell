/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helenebrulin <helenebrulin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:33:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/18 17:51:17 by pmouhali         ###   ########.fr       */
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
	char **sub;

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
	sub = ft_rmfd(args); // can happen here but isnt correct
	ft_tabdel((void**)args);
	if (ft_is_pipe(sub))
		run_dmc_pipes(sub);
	else
		run_dmc(sub);
	dup2(std_out, 1); //reset les sorties
	dup2(std_in, 0);
	ft_tabdel((void**)sub);
	return (0);
}
