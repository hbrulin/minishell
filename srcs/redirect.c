/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:31:29 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/14 15:42:42 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*'>' : rediriger le résultat dans un nouveau fichier. creation si non existant. ecrase si existant.
'>>' : rediriger a la fin d'un fichier. creation si non existant.
'<' : lire depuis un fichier
*/

#include "minishell.h"

int		redirect_right(char *type, char *path_to)
{
	int fd;

	fd = -1;
	if (ft_strcmp(type, ">") == 0)
		fd = open(path_to, O_WRONLY | O_CREAT | O_TRUNC, 0644); //-rw-r--r--
	else if (ft_strcmp(type, ">>") == 0)
		fd = open(path_to, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (1);// securiser
	dup2(fd, 1);
	close(fd);
	return (1);
}

int		redirect_left(char *path_from) //NE PAS EXECUTER LA CMD 1 -> revoir ca -> mauvais ordre? check. tester avec echo
{
	int		fd; 

	if ((fd = open(path_from, O_RDONLY)) < 0)
		return (0);
	dup2(fd, 0);
	close(fd);
	return (1);
}

int		redirect(char **args) //mieux parser pour que pas de prise en compte des arguments > et file
{
	int i = 0;
	char *type;
	char *path;

	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0)
		{
			path = ft_strdup(args[i + 1]);
			type = ft_strdup(args[i]);
			redirect_right(type, path);
			free(type);
			free(path);
		}
		else if (ft_strcmp(args[i], "<") == 0)
		{
			path = ft_strdup(args[i - 1]);
			ft_printf_fd(1, "%s", path);
			redirect_left(path);
			free(path);
		}
		i++;
	}
	return(1);
}
>>>>>>> hbrulin
