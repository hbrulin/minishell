#include "minishell.h"
#include <stdio.h>

/*
**	Receive splitted arguments.
**	args[0] = cmd name
**	DR replace by corresponding env variable
**	BS replace by corresponding char
**	Check for syntax error
*/

char seq[7] = {'\\', '$', '\"', '\'', '|', '<', '>'};

char	*expand_var(char *arg, int dr, int *i) // dr = $ lc = last char of var
{
	char *tmp;
	char *key;

//	printf("received arg: %s\n", arg);
	tmp = ft_substr(arg, dr + 1, *i - 1 - dr);
//	printf("isole var: %s\n", tmp);
	key = ft_strjoin(tmp, "=");
//	printf("var to key: %s\n", key);
	free(tmp);
	tmp = get_var(key);
//	printf("value for key: %s\n", tmp);
	free(key);
	key = ft_strnjoin(arg, tmp, dr); 
//	printf("join previous arg content with interpolated value: %s\n", key);
	free(tmp);
	tmp = ft_strjoin(key, &arg[*i]);
	*i = !key ? -1 : ft_strlen(key);
	free(key);
//	printf("final new arg: %s\n", tmp);
	return (tmp);
}

char	*expand_rvar(char *arg, int *i)
{
	char *tmp;
	char *value;

	value = ft_itoa(g_ret);
	tmp = ft_strnjoin(arg, value, *i - 1); 
	free(value);
	value = ft_strjoin(tmp, &arg[*i + 1]);
	*i = !tmp ? -1 : ft_strlen(tmp);
	free(tmp);
	return (value);
}

int	clean_arg(char **arg)
{
	t_boolean sq;
	t_boolean dq;
	int i;
	int j;
	char *tmp;
	char *s = *arg;

	i = 0;
	sq = FALSE;
	dq = FALSE;
	while (s && s[i])
	{
		if (!sq && !dq && s[i] == 92) // si no mod et escape char escape all
		{
			ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
			i++;
		}
		else if (!sq && dq && s[i] == 92) // si dq et escape char escape all
		{
			j = 0;
			while (j < 3 && seq[j] != s[i + 1])
				j++;
			if (j != 3)
				ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
			i = j == 1 ? i + 2 : i + 1;
		}
		else if (!sq && s[i] == '$')
		{
			j = i;
			i++;
			if (!dq && (s[i] == '\'' || s[i] == '"'))
			{
				ft_memmove(&s[i - 1], &s[i], ft_strlen(s) - (i - 1));
				i--;
			}
			else if (s[i] == '?')
			{
				tmp = s;
				s = expand_rvar(s, &i);
				free(tmp);
				if (i == -1)
					return (1);
			}
			else if (s[i] == '_' || (s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122)) // si first char auth expand else ignore
			{
				while ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122) || (s[i] >= 48 && s[i] <= 57))
					i++;
				tmp = s;
				s = expand_var(s, j, &i);
				free(tmp);
				if (i == -1)
					return (1);
			}
		}
		else if (!sq && !dq && s[i] == 39) // si dq FALSE, sq FALSE, on active et on clear, l'escape n'existe pas en sq mode 
		{
			sq = TRUE;
			ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
		}
		else if (sq && !dq && s[i] == 39) // si sq TRUE, dq FALSE, on desactive et on clear, l'escape n'existe pas en sq mode
		{
			sq = FALSE;
			ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
		}
		else if (!sq && !dq && s[i] == 34) // si sqdq FALSE et single quotes et index = 0 ou index -1 diff de escapechar, on active et on clear 
		{
			dq = TRUE;
			ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
		}
		else if (dq && !sq && s[i] == 34) // si sq TRUE et dq FALSE et pas d'escape derriere on desactive et on clear
		{
			dq = FALSE;
			ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
		}
		else
			i++;
	}
	*arg = s;
	if (sq || dq) // si sq ou dq TRUE la matching quote n'as pas ete trouvee donc syntx error
		return (1);
	return (0);
}
