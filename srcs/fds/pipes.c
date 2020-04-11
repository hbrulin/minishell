/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 20:24:33 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/11 18:43:05 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char **a_cmd)
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
			return (NULL);
		}
		path = build_path(tmp, a_cmd[0]);
		free(tmp);
	}
	if (!path)
		ft_error(CMD_NOT_FOUND, NULL, NULL, a_cmd[0]);
	return (path);
}

t_cmd	*build_cmd(char **a_cmd, int pipeflag)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->path = get_path(a_cmd);
	cmd->arguments = ft_rmfd_pipes(a_cmd);
	cmd->pipe_flag = pipeflag;
	cmd->redirs = build_redir(a_cmd);
	return (cmd);
}

int		loop_cmd(t_pipe_tools *t, char **args)
{
	while (args[t->i])
	{
		if (ft_strcmp(args[t->i], "|") == 0)
		{
			if (!(t->a_cmd = get_cmd(args, t->adv, t->i, 1)))
				return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
			t->cmd[t->k] = build_cmd(t->a_cmd, 1);
			t->k++;
			t->adv = t->i + 1;
			ft_tabdel((void *)t->a_cmd);
			t->j++;
		}
		else if (ft_iter_tab_cmp((char **)&args[t->i + 1], "|"))
		{
			if (!(t->a_cmd = get_cmd(args, t->adv, t->i, 2)))
				return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
			t->cmd[t->k] = build_cmd(t->a_cmd, 0);
			t->k++;
			ft_tabdel((void *)t->a_cmd);
			break ;
		}
		t->i++;
	}
	t->cmd[t->k] = NULL;
	return (0);
}

int		handle_pipes(char **args)
{
	t_pipe_tools	t;
	char			**tab_env;

	ft_bzero(&t, sizeof(t_pipe_tools));
	t.len = count_pip(args) + 1;
	t.cmd = malloc(sizeof(t_cmd) * t.len);
	if (loop_cmd(&t, args))
		return (1);
	if (!(tab_env = ft_lst_to_tab(g_env)))
		return (ft_strerror(NULL, NULL, NULL, NULL));
	g_ret = execute_cmds(t.cmd, tab_env);
	is_forking(0);
	free_t_cmd(t.cmd);
	ft_tabdel((void *)tab_env);
	return (0);
}
