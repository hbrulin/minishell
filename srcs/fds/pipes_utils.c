/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 16:38:04 by hbrulin           #+#    #+#             */
/*   Updated: 2020/03/11 18:51:54 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_cmd(t_cmd *cmd, int len)
{
	int i;

	i = 0;
	if (cmd)
	{
		while (i < len)
		{
			if (cmd[i].path)
				free(cmd[i].path);
			if (cmd[i].argv)
				ft_tabdel((void *)cmd[i].argv);
			i++;
		}
		free(cmd);
	}
}


void	handle_sig_pipes(int status)
{
	g_ret = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_ret = SIG_CODE + WTERMSIG(status);
	if (WTERMSIG(status) == 2)
		ft_putstr("\n");
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

int		count_pipes(char **args)
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
