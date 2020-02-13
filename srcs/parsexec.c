/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:33:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/12 16:31:21 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsexec(char *cmd)
{
	if (!cmd)
		return(0);
	char **args = NULL;

	if(!(args = parse_arg(cmd)))
		return(ft_error(MALLOC_FAIL, 1, cmd, NULL));
	free(cmd);
	if (interpreter(args) == 1)
		return(ft_error_tab(SYNTAX_ERR, 0, args, NULL));
	//launch redirect
	if (run_dmc(args))
		return(ft_error_tab(NULL, 1, args, NULL));
	ft_tabdel((void *)args); 
	return(0);
}
