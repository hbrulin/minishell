//header

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
