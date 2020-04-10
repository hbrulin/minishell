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

t_redir		*make_tmp(int dir, char *file)
{
	t_redir *tmp;
	tmp = malloc(sizeof(t_cmd));
	tmp->direction = dir;
	tmp->name = ft_strdup(file);
	return (tmp);
}

t_redir **build_redir(char ** a_cmd)
{
	t_redir **redirs;
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
            redirs[j] = make_tmp(OUTPUT, a_cmd[i + 1]);
            j++;
		}
        else if ((ft_strcmp(a_cmd[i], ">>") == 0 && ft_strcmp(a_cmd[i - 1], "\\")))
		{
			redirs[j] = make_tmp(APPEND, a_cmd[i + 1]);
            j++;
		}
		else if ((ft_strcmp(a_cmd[i], "<") == 0 && ft_strcmp(a_cmd[i - 1], "\\")))
		{
			redirs[j] = make_tmp(INPUT, a_cmd[i + 1]);
            j++;
		}
		i++;
	}
    redirs[j] = NULL;
    return (redirs);
}