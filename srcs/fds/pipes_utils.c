/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 20:26:54 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/10 20:30:41 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirs(t_redir **redirs)
{
	int i;

	i = 0;
	if (!redirs)
		return ;
	while (redirs[i])
	{
		free(redirs[i]->name);
		free(redirs[i]);
		i++;
	}
	free(redirs);
}

void	free_t_cmd(t_cmd **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]->path);
		ft_tabdel((void *)cmd[i]->arguments);
		free_redirs(cmd[i]->redirs);
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

int		count_pip(char **args)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (!(ft_strcmp(args[i], "|")))
			count++;
		i++;
	}
	return (count);
}

char	**get_cmd(char **args, int adv, int i, int flag)
{
	char **cmd;

	if (flag == 1)
	{
		if (adv == 0)
		{
			if (!(cmd = ft_sub_tab(args, adv, i)))
				return (NULL);
		}
		else
		{
			if (!(cmd = ft_sub_tab(args, adv, (ft_tab_chr_i((char **)&args[adv],
				"|")))))
				return (NULL);
		}
	}
	if (flag == 2)
	{
		if (!(cmd = ft_sub_tab(args, i, ft_tablen(args) - i)))
			return (NULL);
	}
	return (cmd);
}
