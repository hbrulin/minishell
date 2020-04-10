/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helenebrulin <helenebrulin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:56:35 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/10 18:05:23 by helenebruli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirs(t_redir **redirs)
{
	int i = 0;
	if (!redirs)
		return;
	while (redirs[i])
	{
		free(redirs[i]->name);
		i++;
	}
	free(redirs);
}

void	free_t_cmd(t_cmd **cmd)
{
	int i = 0;
	while (cmd[i])
	{
		free(cmd[i]->path);
		ft_tabdel((void *)cmd[i]->arguments);
		free_redirs(cmd[i]->redirs);
		i++;
	}
	free(cmd);
}

char 	**get_cmd(char **args, int adv, int i, int flag)
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

t_cmd	*build_cmd(char **a_cmd, int pipeflag)
{
	char	*path;
	char	*tmp;

	path = ft_strrchr(a_cmd[0], '/');
	if (path && !(path = ft_strdup(try_path(a_cmd[0]))))
	{
		ft_strerror(NULL, NULL, a_cmd[0], NULL);
		return (NULL);
	}
	else if (!path)
	{
		if (!(tmp = get_var(g_env, "PATH=")))
		{
			g_ret = 127;
			ft_error(NO_FILE, path, NULL, a_cmd[0]);
			
		}
		path = build_path(tmp, a_cmd[0]);
		free(tmp);
	}
	if (!path)
	{
		ft_error(CMD_NOT_FOUND, NULL, NULL, a_cmd[0]);
		
	}

	t_redir **redirs = build_redir(a_cmd);
	char	**args = ft_rmfd_pipes(a_cmd);
	t_cmd *cmd = malloc(sizeof(t_cmd));

	cmd->path = path;
	cmd->arguments = args;
	cmd->pipe_flag = pipeflag;
	cmd->redirs = redirs;
	return (cmd);
}

int		handle_pipes(char **args)
{
	t_pipe_tools	t;
	int				len;
	t_cmd			**cmd;
	int				j;
	int k = 0;

	len = count_pip(args) + 1;
	ft_bzero(&t, sizeof(t_pipe_tools));
	cmd = malloc(sizeof(t_cmd) * len);
	j = 0;
	while (args[t.i])
	{
		if (ft_strcmp(args[t.i], "|") == 0)
		{
			if (!(t.a_cmd = get_cmd(args, t.adv, t.i, 1)))
				return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
			cmd[k] = build_cmd(t.a_cmd, 1); //prevoir si erreur path
			k++;
			t.adv = t.i + 1;
			ft_tabdel((void *)t.a_cmd);
			j++;
		}
		else if (ft_iter_tab_cmp((char **)&args[t.i + 1], "|"))
		{
			if (!(t.a_cmd = get_cmd(args, t.adv, t.i, 2)))
				return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
			cmd[k] = build_cmd(t.a_cmd, 0); //prevoir si erreur path
			k++;
			ft_tabdel((void *)t.a_cmd);
			break ;
		}
		t.i++;
	}
	cmd[k] = NULL;

	char	**tab_env;
	tab_env = NULL;
	if (!(tab_env = ft_lst_to_tab(g_env)))
		return (ft_strerror(NULL, NULL, NULL, NULL));
	g_ret = execute_cmds(cmd, tab_env);
	is_forking(0); //modif ici
	free_t_cmd(cmd);
	free(tab_env);
	return (0);
}