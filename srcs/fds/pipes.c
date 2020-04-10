/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 20:24:33 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/10 20:31:04 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*build_cmd(char **a_cmd, int pipeflag)
{
	char	*path;
	char	*tmp;
	t_redir **redirs;
	char	**args;
	t_cmd	*cmd;

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
		ft_error(CMD_NOT_FOUND, NULL, NULL, a_cmd[0]);
	redirs = build_redir(a_cmd);
	args = ft_rmfd_pipes(a_cmd);
	cmd = malloc(sizeof(t_cmd));
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
	int				k;
	char			**tab_env;

	len = count_pip(args) + 1;
	ft_bzero(&t, sizeof(t_pipe_tools));
	cmd = malloc(sizeof(t_cmd) * len);
	j = 0;
	k = 0;
	while (args[t.i])
	{
		if (ft_strcmp(args[t.i], "|") == 0)
		{
			if (!(t.a_cmd = get_cmd(args, t.adv, t.i, 1)))
				return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
			cmd[k] = build_cmd(t.a_cmd, 1);
			k++;
			t.adv = t.i + 1;
			ft_tabdel((void *)t.a_cmd);
			j++;
		}
		else if (ft_iter_tab_cmp((char **)&args[t.i + 1], "|"))
		{
			if (!(t.a_cmd = get_cmd(args, t.adv, t.i, 2)))
				return (g_ret = ft_strerror(NULL, NULL, NULL, NULL));
			cmd[k] = build_cmd(t.a_cmd, 0);
			k++;
			ft_tabdel((void *)t.a_cmd);
			break ;
		}
		t.i++;
	}
	cmd[k] = NULL;
	if (!(tab_env = ft_lst_to_tab(g_env)))
		return (ft_strerror(NULL, NULL, NULL, NULL));
	g_ret = execute_cmds(cmd, tab_env);
	is_forking(0);
	free_t_cmd(cmd);
	ft_tabdel((void *)tab_env);
	return (0);
}
