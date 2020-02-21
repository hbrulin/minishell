/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:45:11 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/21 16:32:38 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*try_path(char *path)
{
	struct stat	file;

	errno = 0;
	stat(path, &file);
	if (errno)
		return (NULL);
	if ((file.st_mode & S_IFMT) == S_IFDIR && (errno = EISDIR))
		return (NULL);
	return (path);
}
