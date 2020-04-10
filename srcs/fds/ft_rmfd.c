/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rmfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:25:43 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/10 19:26:11 by hbrulin          ###   ########.fr       */
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
		if ((args[i][0] == '<' || args[i][0] == '>') &&
			ft_strcmp(args[i - 1], "\\"))
			count++;
		i++;
	}
	return (count);
}

char	**ft_rmfd(char **args, char **sub)
{
	t_redir_tools t;

	ft_bzero(&t, sizeof(t_redir_tools));
	if (ft_count(args) == 0)
		return (sub = copy_tab(args));
	t.len = ft_tablen(args) - (ft_count(args) * 2);
	if (!(sub = (char **)malloc(sizeof(char *) * (t.len + 1))))
		return (NULL);
	sub[t.len] = 0;
	while (args[t.i])
	{
		if ((args[t.i][0] == '<' || args[t.i][0] == '>') &&
			ft_strcmp(args[t.i - 1], "\\"))
			t.i++;
		else if ((args[t.i][0] != '<' && args[t.i][0] != '>') ||
			!ft_strcmp(args[t.i - 1], "\\"))
		{
			if (!(sub[t.j] = ft_strdup(args[t.i])))
				return (NULL);
			t.j++;
		}
		t.i++;
	}
	return (sub);
}

char	**ft_rmfd_pipes(char **args)
{
	t_redir_tools	t;
	char			**sub;

	ft_bzero(&t, sizeof(t_redir_tools));
	if (ft_count(args) == 0)
		return (sub = copy_tab(args));
	t.len = ft_tablen(args) - (ft_count(args) * 2);
	if (!(sub = (char **)malloc(sizeof(char *) * (t.len + 1))))
		return (NULL);
	sub[t.len] = 0;
	while (args[t.i])
	{
		if ((args[t.i][0] == '<' || args[t.i][0] == '>') &&
			ft_strcmp(args[t.i - 1], "\\"))
			t.i++;
		else if ((args[t.i][0] != '<' && args[t.i][0] != '>') ||
			!ft_strcmp(args[t.i - 1], "\\"))
		{
			if (!(sub[t.j] = ft_strdup(args[t.i])))
				return (NULL);
			t.j++;
		}
		t.i++;
	}
	return (sub);
}
