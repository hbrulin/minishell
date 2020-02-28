/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_part.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 15:37:18 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/28 17:15:33 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char **args, int i)
{
	int		j;
	char	*tmp;

	j = 1;
	tmp = ft_strdup(args[i]);
	while (args[i][j] != '\"' && args[i][j])
		j++;
	tmp[j] = '=';
	ft_memmove(&(tmp)[0], &(tmp)[2], ft_strlen(tmp));
	return (tmp);
}

void	loop_arg(char **args)
{
	int		i;
	char	*tmp;
	char	*var;

	i = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "\"\"") || !ft_strcmp(args[i], "\'\'"))
			g_ret = ft_error(NO_FILE_LS, NULL, NULL, NULL);
		else if (args[i][0] == '\"' && args[i][1] == '$')
		{
			tmp = get_key(args, i);
			if (!(var = get_var(g_env, tmp)))
				g_ret = ft_error(NO_FILE_LS, NULL, NULL, NULL);
			free(tmp);
			if (var)
				free(var);
		}
		i++;
	}
}

int		ls_part(char **args)
{
	char	*tmp;
	char	*var;

	if (ft_tablen(args) < 2)
		return (0);
	if ((!ft_strcmp(args[1], "\"\"") || !ft_strcmp(args[1], "\'\'"))
		&& !args[2])
		return (g_ret = ft_error(NO_FILE_LS, NULL, NULL, NULL));
	else if (args[1][0] == '\"' && args[1][1] == '$')
	{
		tmp = get_key(args, 1);
		if (!(var = get_var(g_env, tmp)))
			return (g_ret = ft_error(NO_FILE_LS, NULL, NULL, NULL));
		free(tmp);
		free(var);
	}
	loop_arg(args);
	return (0);
}
