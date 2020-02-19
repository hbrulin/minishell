/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:33:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/19 15:37:55 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_pipe(char **args)
{
	int i;

	if (!args)
		return (0);
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
	char	**sub;

	std_in = dup(0);
	std_out = dup(1);
	if (!cmd)
		return (0);
	if(!(args = parse_arg(cmd)))
		return (g_ret = ft_error(SYNTAX_ERR, cmd, NULL, NULL));
	free(cmd);
	if(!(sub = redirect(args)))
		return (g_ret = ft_error(NULL, NULL, args, NULL));
	ft_tabdel((void *)args);
	if (ft_is_pipe(sub))
		run_dmc_pipes(sub);
	else
		run_dmc(sub); 
	dup2(std_out, 1); //reset les sorties
	dup2(std_in, 0);
	return (0);
}
