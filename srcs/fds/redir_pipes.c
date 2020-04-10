#include "minishell.h"

int		count_redir(char **args)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (!(ft_strcmp(args[i], "<")) || !(ft_strcmp(args[i], ">")) || !(ft_strcmp(args[i], ">>")) )
			count++;
		i++;
	}
	return (count);
}

t_redir **build_redir(char ** a_cmd)
{
	t_redir **redirs;
    t_redir tmp;
	int				len;
    int i = 0;
    int j = 0;

    if (!(ft_tab_chr(a_cmd, "<")) && !(ft_tab_chr(a_cmd, ">")) && !(ft_tab_chr(a_cmd, ">>")))
        return (NULL);

	len = count_redir(a_cmd) + 1;
	redirs = malloc(sizeof(t_cmd) * len);

    while (a_cmd[i])
	{
		if ((ft_strcmp(a_cmd[i], ">") == 0 && ft_strcmp(a_cmd[i - 1], "\\")))
		{
            tmp.direction = OUTPUT;
	    	tmp.name = ft_strdup(a_cmd[i + 1]);
            redirs[j] = &tmp;
            j++;
		}
        else if ((ft_strcmp(a_cmd[i], ">>") == 0 && ft_strcmp(a_cmd[i - 1], "\\")))
		{
			tmp.direction = APPEND;
	    	tmp.name = ft_strdup(a_cmd[i + 1]);
            redirs[j] = &tmp;
            j++;
		}
		else if ((ft_strcmp(a_cmd[i], "<") == 0 && ft_strcmp(a_cmd[i - 1], "\\")))
		{
			tmp.direction = INPUT;
	    	tmp.name = ft_strdup(a_cmd[i + 1]);
            redirs[j] = &tmp;
            j++;
		}
		i++;
	}
    redirs[j] = NULL;
    return (redirs);
}