/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:11:41 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/03 16:24:07 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

//mettre dans libft
size_t		ft_tablen(char **arr)
{
	size_t i;

	i = 0;
	if (arr)
		while (arr[i])
			i++;
	return (i);
}

char **copy_tab(char **envp)
{
	char **cpy;
	char **cpy_ret;
	size_t len;

	if (!(len = ft_tablen(envp)))
		return (NULL);
	if (!(cpy = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	cpy_ret = cpy;
	cpy[len] = NULL;
	while (len--)
		*cpy++ = ft_strdup(*envp++);
	return(cpy_ret);
}
