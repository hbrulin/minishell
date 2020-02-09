/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 11:09:00 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/09 14:34:43 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    set_var(char *key, char *value)
{
    int i;
    char * tmp;

    i = 0;
	while(g_env[i])
	{
		if (ft_strncmp(g_env[i], key, ft_strlen(key)) == 0)
        {
            tmp = ft_strjoin(key, value);
            free(g_env[i]);
            g_env[i] = ft_strdup(tmp);
			free(tmp);
        }
		i++;
	}
}

char    *get_var(char *key)
{
    int i;
    char *tmp = NULL;

    i = 0;
	while(g_env[i])
	{
		if (ft_strncmp(g_env[i], key, ft_strlen(key)) == 0)
            tmp = ft_substr(g_env[i], ft_strlen(key), ft_strlen(g_env[i]) - ft_strlen(key));
		i++;
	}
    return (tmp);
}
