/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:31:29 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/19 14:13:55 by hbrulin          ###   ########.fr       */
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
		return(ft_error("minishell: %s: No such file or directory\n", NULL, NULL, path_to));
	dup2(fd, 1);
	close(fd);
	return (0);
}

int		redirect_left(char *path_from) //NE PAS EXECUTER LA CMD 1 -> revoir ca -> mauvais ordre? check. tester avec echo
{
	int		fd; 

	if ((fd = open(path_from, O_RDONLY)) < 0)
		return(ft_error("minishell: %s: No such file or directory\n", NULL, NULL, path_from));
	dup2(fd, 0);
	close(fd);
	return (0);
}

int ft_count(char **args)
{
	int i;
    int count;

    i = 0;
    count = 0;
    while (args[i])
    {
         if (args[i][0] == '<' || args[i][0] == '>' )
            count++;
        i++;
    }
    return(count);
}

char **redirect(char **args) //mieux parser pour que pas de prise en compte des arguments > et file
{
	int i = 0;
	char *type;
	char *path;
	char **sub;

	int count = ft_count(args);
	if (count == 0)
	{
		sub = copy_tab(args);
		return (sub);
	}
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0)
		{
			path = ft_strdup(args[i + 1]);
			type = ft_strdup(args[i]);
			if(redirect_right(type, path))
				return (NULL);
			free(type);
			free(path);
		}
		else if (ft_strcmp(args[i], "<") == 0)
		{
			path = ft_strdup(args[i + 1]);
			ft_printf_fd(1, "%s", path);
			if(redirect_left(path))
				return(NULL);
			free(path);
		}
		i++;
	}
	sub = ft_rmfd(args, count);
	return(sub);
}
