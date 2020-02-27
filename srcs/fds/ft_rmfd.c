/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rmfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:11:24 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/27 14:07:34 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_count(char **args)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if ((args[i][0] == '<' || args[i][0] == '>') && ft_strcmp(args[i - 1], "\\"))
			count++;
		i++;
	}
	return (count);
}

char	**ft_rmfd(char **args, char **sub)
{
	int		i;
	int		len;
	int		j;

	if (ft_count(args) == 0)
		return (sub = copy_tab(args));
	len = ft_tablen(args) - (ft_count(args) * 2);
	if (!(sub = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	sub[len] = 0;
	i = 0;
	j = 0;
	while (args[i])
	{
		if ((args[i][0] == '<' || args[i][0] == '>') && ft_strcmp(args[i - 1], "\\"))
			i++;
		else if ((args[i][0] != '<' && args[i][0] != '>') || !ft_strcmp(args[i - 1], "\\"))
		{
			if (!(sub[j] = ft_strdup(args[i])))
				return (NULL);
			j++;
		}
		i++;
	}
	return (sub);
}
