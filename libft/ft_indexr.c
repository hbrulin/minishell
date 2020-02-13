// HEADER

#include "libft.h"

int		ft_indexr(const char *s, int c)
{
	int i;

	i = ft_strlen(s);
	while (s && --i >= 0)
		if (s[i] == c)
			return (i);
	return (-1);
}
