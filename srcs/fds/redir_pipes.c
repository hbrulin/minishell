/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:36:39 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/10 19:48:34 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			count_redir(char **args)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (!(ft_strcmp(args[i], "<")) || !(ft_strcmp(args[i], ">"))
			|| !(ft_strcmp(args[i], ">>")))
			count++;
		i++;
	}
	return (count);
}

t_redir		*make_tmp(int dir, char *file)
{
	t_redir *tmp;

	tmp = malloc(sizeof(t_cmd));
	tmp->direction = dir;
	tmp->name = ft_strdup(file);
	return (tmp);
}

void		fill_redirs(t_redir **redirs, char **a_cmd, int i, int j)
{
	while (a_cmd[i])
	{
		if ((ft_strcmp(a_cmd[i], ">") == 0 && ft_strcmp(a_cmd[i - 1], "\\")))
		{
			redirs[j] = make_tmp(OUTPUT, a_cmd[i + 1]);
			j++;
		}
		else if ((ft_strcmp(a_cmd[i], ">>") == 0 && ft_strcmp(a_cmd[i - 1],
			"\\")))
		{
			redirs[j] = make_tmp(APPEND, a_cmd[i + 1]);
			j++;
		}
		else if ((ft_strcmp(a_cmd[i], "<") == 0 && ft_strcmp(a_cmd[i - 1],
			"\\")))
		{
			redirs[j] = make_tmp(INPUT, a_cmd[i + 1]);
			j++;
		}
		i++;
	}
	redirs[j] = NULL;
}

t_redir		**build_redir(char **a_cmd)
{
	t_redir **redirs;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(ft_tab_chr(a_cmd, "<")) && !(ft_tab_chr(a_cmd, ">"))
		&& !(ft_tab_chr(a_cmd, ">>")))
		return (NULL);
	len = count_redir(a_cmd) + 1;
	redirs = malloc(sizeof(t_cmd) * len);
	fill_redirs(redirs, a_cmd, i, j);
	return (redirs);
}
