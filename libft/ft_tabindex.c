//HEADER

#include "libft.h"

int		ft_tabindex(const char **tab, const char *s)
{
	int i;

	i = -1;
	while (tab && tab[++i])
		if (s && !ft_strcmp(tab[i], s))
			return (i);
	return (-1);
}
