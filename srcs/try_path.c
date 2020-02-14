/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmouhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:20:13 by pmouhali          #+#    #+#             */
/*   Updated: 2020/02/14 13:20:37 by pmouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*try_path(char *path, int *error)
{
	struct stat	file;

	*error = stat(path, &file);
	if (*error && (*error = errno))
		return (NULL);
	if ((file.st_mode & S_IFMT) == S_IFDIR && (*error = EISDIR))
		return (NULL);
	return (path);
}
