/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 19:06:16 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/12 15:06:34 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			input(t_redir **redirs, t_fd *redir_fd)
{
	if ((*redir_fd = open((*redirs)->name, O_RDONLY)) == ERROR)
	{
		perror((*redirs)->name);
		exit(errno);
	}
	if (dup2(*redir_fd, STDIN) == ERROR)
	{
		perror("dup input redirection");
		exit(errno);
	}
}

void			output(t_redir **redirs, t_fd *redir_fd)
{
	if ((*redir_fd =
		open((*redirs)->name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == ERROR)
	{
		perror((*redirs)->name);
		exit(errno);
	}
	if (dup2(*redir_fd, STDOUT) == ERROR)
	{
		perror("dup output redirection");
		exit(errno);
	}
}

void			append(t_redir **redirs, t_fd *redir_fd)
{
	if ((*redir_fd = open((*redirs)->name,
		O_WRONLY | O_CREAT | O_APPEND, 0644)) == ERROR)
	{
		perror((*redirs)->name);
		exit(errno);
	}
	if (dup2(*redir_fd, STDOUT) == ERROR)
	{
		perror("dup append redirection");
		exit(errno);
	}
}
