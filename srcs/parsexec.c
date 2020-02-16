/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:33:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/14 22:05:18 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_pipe(char **args)
{
	int i = 0;

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
	char 	**args = NULL;

	std_in = dup(0);
	std_out = dup(1);
	if (!cmd)
		return(0);
	if(!(args = parse_arg(cmd)))
		return(ft_error(SYNTAX_ERR, cmd, NULL, NULL));
	free(cmd);
	if (interpreter(args) == 1)
		return(ft_error(SYNTAX_ERR, NULL, args, NULL));
	redirect(args);
	if (ft_is_pipe(args))
		run_dmc_pipes(args);
	else
		run_dmc(args);
	ft_tabdel((void *)args); 
	dup2(std_out, 1); //reset les sorties
	dup2(std_in, 0);
	return(0);
}
