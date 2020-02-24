/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:51:49 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/20 13:49:34 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_operand(char *s)
{
	if ((!ft_strcmp(s, "|")) || (!ft_strcmp(s, "<")) ||
		(!ft_strcmp(s, ">")) || (!ft_strcmp(s, ">>")))
		return (1);
	return (0);
}

int		ft_is_operand(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int		check_error_syntax(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '|' && ft_strlen(args[i]) > 1)
			return (1);
		else if (args[i][0] == '>' && ft_strlen(args[i]) > 2)
			return (1);
		else if ((args[i][0] == '<' || args[i][0] == '>') &&
			ft_strlen(args[i]) > 1 && args[i][1] == '|')
			return (1);
		else if (args[i][0] == '<' && ft_strlen(args[i]) > 1 && args[i][1] != '>')
			return (1);
		else if (args[i][0] == '>' && args[i][1] == '<')
			return (1);
		if (args[i + 1])
		{
			if (check_operand(args[i]) && check_operand(args[i + 1]))
				return (1);
		}
		else if (check_operand(args[i]) && !args[i + 1])
			return (1);
		i++;
	}
	return (0);
}
