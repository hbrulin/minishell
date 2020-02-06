/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:33:52 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 13:37:19 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	run_dmc(char **args)
{
	if (!args || !*args || !**args)
		return (1);
	if ((ft_strcmp(args[0], "exit") == 0))
	{
		//TODO
	}
	else
		ft_printf("minishell: %s: command not found", args[0]);
	return(1);
}
