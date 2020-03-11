/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 11:25:00 by hbrulin           #+#    #+#             */
/*   Updated: 2020/03/11 14:14:59 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		redirect_right_p(char *type, char *path_to, int *pipe_fd)
{
	int fd;

	fd = -1;
	if (ft_strcmp(type, ">") == 0)
		fd = open(path_to, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(type, ">>") == 0)
		fd = open(path_to, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (ft_error(RNO_FILE, NULL, NULL, path_to));
	dup2(fd, 1);
	(void)pipe_fd;
	close(fd);
	//close (pipe_fd[1]);
	return (0);
}

int		redirect_left_p(char *path_from, int *pipe_fd)
{
	int		fd;
	(void)pipe_fd;
	if ((fd = open(path_from, O_RDONLY)) < 0)
		return (ft_error(RNO_FILE, NULL, NULL, path_from));
	dup2(fd, 0);
	close(fd);
	return (0);
}

char	**redirect_pipes(char **args, int *pipe_fd)
{
	int		i;
	char	**sub;

	sub = NULL;
	i = 0;
	while (args[i])
	{
		if ((ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0)
			&& ft_strcmp(args[i - 1], "\\"))
		{
			if (redirect_right_p(args[i], args[i + 1], pipe_fd))
				return (NULL);
		}
		else if (ft_strcmp(args[i], "<") == 0 && ft_strcmp(args[i - 1], "\\"))
		{
			if (redirect_left_p(args[i + 1], pipe_fd))
				return (NULL);
		}
		i++;
	}
	return (sub = ft_rmfd(args, sub));
}
