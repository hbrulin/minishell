/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_part.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 15:37:18 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/28 16:59:45 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int		ls_part(char **args)
{
	int i = 0;
	int j;
	char *tmp;
	char *var;

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
		j = 1;
		tmp = ft_strdup(args[1]);
		while (args[1][j] != '\"' && args[1][j])
			j++;
		tmp[j] = '=';
		ft_memmove(&(tmp)[0], &(tmp)[2], ft_strlen(tmp));
		if (!(var = get_var(g_env, tmp)))
		{
			g_ret = 1;
			ft_printf_fd(2, "ls: : No such file or directory\n");
			return (ft_error(NULL, tmp, NULL, NULL));
		}
		free(tmp);
		free(var);
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
			j = 1;
			tmp = ft_strdup(args[i]);
			while (args[i][j] != '\"' && args[i][j])
				j++;
			tmp[j] = '=';
			ft_memmove(&(tmp)[0], &(tmp)[2], ft_strlen(tmp));
			if (!(var = get_var(g_env, tmp)))
			{
				g_ret = 1;
				ft_printf_fd(2, "ls: : No such file or directory\n");
			}
			free(tmp);
			if (var)
				free(var);
		}
		i++;
	}
	return (0);
}
