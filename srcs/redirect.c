/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:31:29 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/21 16:11:47 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		redirect_right(char *type, char *path_to)
{
	int fd;

	fd = -1;
	if (ft_strcmp(type, ">") == 0)
		fd = open(path_to, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(type, ">>") == 0)
		fd = open(path_to, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return(ft_error(RNO_FILE, NULL, NULL, path_to));
	dup2(fd, 1);
	close(fd);
	return (0);
}

int		redirect_left(char *path_from)
{
	int		fd; 

	if ((fd = open(path_from, O_RDONLY)) < 0)
		return(ft_error(RNO_FILE, NULL, NULL, path_from));
	dup2(fd, 0);
	close(fd);
	return (0);
}

int		ft_create(char *path)
{
	int fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return(ft_error(RNO_CREA, NULL, NULL, path));
	return (0);
}

char	**redirect(char **args)
{
	int i = 0;
	char **sub;

	sub = NULL;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0)
		{
			if(redirect_right(args[i], args[i + 1]))
				return (NULL);
		}
		else if (ft_strcmp(args[i], "<") == 0)
		{
			if(redirect_left(args[i + 1]))
				return(NULL);
		}
		else if (ft_strcmp(args[i], "<>") == 0)
		{
			if(ft_create(args[i + 1]))
				return(NULL);
		}
		i++;
	}
	sub = ft_rmfd(args, sub);
	return(sub);
}
