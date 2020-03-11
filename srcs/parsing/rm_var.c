/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 21:04:35 by hbrulin           #+#    #+#             */
/*   Updated: 2020/03/11 21:11:59 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_rm(char **args)
{
	char	*key;
	char	*tmp;
	int i = 0;
	int j = 0;
	int k;
	int count = 0;

	while (args[i])
	{
		j = 0;
		if (args[i][j] == '$')
		{
			k = j + 1;
			while (args[i][k] != '\"' && args[i][k])
				k++;
			if (!(key = ft_substr(args[i], j + 1, k - 1)))
				return (-1);
			if ((tmp = get_var(g_env, key)) != NULL)
				count++;
			free(tmp);
			free(key);
		}
		else
			count++;
		i++;
	}
	return (count);
}

char	**rm_wrong_var(char **args)
{
	char	**cpy;
	char	*key;
	char	*tmp;
	int i = 0;
	int j = 0;
	int k;
	int l = 0;
	int count;

	if ((count = count_rm(args)) == -1)
		return (NULL);
	if(!(cpy = (char **)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	cpy[count] = NULL;
	while (args[i])
	{
		j = 0;
		if (args[i][j] == '$')
		{
			k = j + 1;
			while (args[i][k] != '\"' && args[i][k])
				k++;
			if(!(key = ft_substr(args[i], j + 1, k - 1)))
				return (NULL);
			if ((tmp = get_var(g_env, key)) != NULL)
			{
				if (!(cpy[l] = ft_strdup(args[i])))
					return (NULL);
				l++;
			}
			free(tmp);
			free(key);
		}
		else
		{
			if (!(cpy[l] = ft_strdup(args[i])))
				return (NULL);
			l++;
		}
		i++;
	}
	return (cpy);
}
