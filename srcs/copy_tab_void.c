#include "minishell.h"

size_t		ft_tablen_void(char **tab)
{
	size_t	count;
	int		i;

	i = 0;
	count = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (ft_strcmp(tab[i], ""))
				count++;
			i++;
		}
	}
	return (count);
}

char	**copy_tab_void(char **tab)
{
	char	**cpy;
	char	**cpy_ret;
	size_t	len;
	int		i;

	i = 0;
	if (!(len = ft_tablen_void(tab)))
		return (NULL);
	if (!(cpy = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	cpy_ret = cpy;
	cpy[len] = NULL;
	len = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], ""))
		{
			if (!(cpy[len] = ft_strdup(tab[i])))
				return (NULL);
			len++;
		}
		i++;
	}
	return (cpy_ret);
}
