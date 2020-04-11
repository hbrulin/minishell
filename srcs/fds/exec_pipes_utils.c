/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:55:47 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/11 19:12:16 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			apply_redirs(t_redir **redirs)
{
	t_fd	redir_fd;

	while (*redirs)
	{
		if ((*redirs)->direction == INPUT)
			input(redirs, &redir_fd);
		else if ((*redirs)->direction == OUTPUT)
			output(redirs, &redir_fd);
		if ((*redirs)->direction == APPEND)
			append(redirs, &redir_fd);
		close(redir_fd);
		redirs++;
	}
}

t_status		ret_status(t_pid last_pid)
{
	t_pid		pid;
	t_status	status;
	t_status	last_status;

	is_forking(3);
	while ((pid = waitpid(-1, &status, 0)) != ERROR)
		if (pid == last_pid)
			last_status = status;
	if (errno != ECHILD)
	{
		perror("wait pipe childs");
		return (errno);
	}
	return (last_status);
}

t_size			count_pipes(t_cmd **cmds)
{
	t_size		len;

	len = 1;
	while (cmds[len]->pipe_flag)
		len++;
	return (len + 1);
}

void			create_pipeline(t_cmd **cmds, t_cmd **pipeline)
{
	t_index		i;

	i = 0;
	while (cmds[i]->pipe_flag)
	{
		pipeline[i] = cmds[i];
		i++;
	}
	pipeline[i] = cmds[i];
	pipeline[i + 1] = NULL;
}
