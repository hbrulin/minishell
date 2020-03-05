/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:24:25 by fhenrion          #+#    #+#             */
/*   Updated: 2020/03/05 17:03:27 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define ERROR -1
#define EXIT_ERROR(message) { perror(message); exit(errno);}

typedef struct	s_cmd
{
	char		*path;
	char		*argv[3];
}				t_cmd;

void	execute_pipes(t_cmd *cmd, size_t index, size_t len, int parent_fd[2])
{
	pid_t	pid;
	int		pipe_fd[2];

	if (index < len - 1)
	{
		if (pipe(pipe_fd) == ERROR)
			EXIT_ERROR("pipe");
		if ((pid = fork()) == ERROR)
			EXIT_ERROR("fork");
		if (pid == 0)
			execute_pipes(cmd, index + 1, len, pipe_fd);
		dprintf(2, "dup out cmd %lu\n", index);
		if (dup2(pipe_fd[0], STDIN_FILENO) == ERROR)
			EXIT_ERROR("dup2");
		if (close(pipe_fd[1]) == ERROR)
			EXIT_ERROR("close");
		if (close(pipe_fd[0]) == ERROR)
			EXIT_ERROR("close");
		dprintf(2, "wait cmd %lu\n", index);
		wait(NULL);
	}
	if (index)
	{
		dprintf(2, "dup in cmd %lu\n", index);
		if (dup2(parent_fd[1], STDOUT_FILENO) == ERROR)
			EXIT_ERROR("dup2");
		if (close(parent_fd[0]) == ERROR)
			EXIT_ERROR("close");
		if (close(parent_fd[1]) == ERROR)
			EXIT_ERROR("close");
	}
	dprintf(2, "exec cmd %lu\n", index);
	
	if (execv(cmd[index].path, cmd[index].argv) == ERROR)
		EXIT_ERROR("execv");
}

int		main(int ac, char *av[])
{
	pid_t	pid;
	t_cmd	piped_cmds[3];

	if (ac != 1)
		return (0);
	piped_cmds[0].path = strdup("/usr/bin/wc");
	piped_cmds[0].argv[0] = strdup("wc");
	piped_cmds[0].argv[1] = NULL;
	piped_cmds[1].path = strdup("/usr/bin/wc");
	piped_cmds[1].argv[0] = strdup("wc");
	piped_cmds[1].argv[1] = NULL;
	piped_cmds[2].path = strdup("/bin/ls");
	piped_cmds[2].argv[0] = strdup("ls");
	piped_cmds[2].argv[2] = strdup("..");
	piped_cmds[2].argv[2] = NULL;
	execute_pipes(piped_cmds, 0, 3, 0);
	return (EXIT_SUCCESS);
}
