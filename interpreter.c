#include "minishell.h"

void	expand_envvar(char **arg, int dr, int *i)
{
	char *tmp;
	char *key;

	tmp = ft_substr(*arg, dr + 1, (*i - 1) - dr);
	key = ft_strjoin(tmp, "=");
	free(tmp);
	tmp = get_var(env, key);
	free(key);
	key = ft_strnjoin(*arg, tmp, dr); 
	free(tmp);
	tmp = ft_strjoin(key, &((*arg)[*i]));
	*i = !key ? -1 : ft_strlen(key);
	free(key);
	key = *arg;
	*arg = tmp;
	free(key);
}

void	expand_resvar(char **arg, int *i)
{
	char *tmp;
	char *value;

	value = ft_itoa(g_ret);
	tmp = ft_strnjoin(*arg, value, *i - 1); 
	free(value);
	value = ft_strjoin(tmp, &((*arg)[*i + 1]));
	*i = !tmp ? -1 : ft_strlen(tmp);
	free(tmp);
	tmp = *arg;
	*arg = value;
	free(tmp);
}

int		envvar_authorized_character(char c, int first_char)
{
	if (first_char == TRUE)
		if (c == '_' || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
			return (TRUE);
	if (first_char == FALSE)
		if ((c > 64 && c < 91) || (c > 96 && c < 123) || (c > 47 && c < 58))
			return (TRUE);
	return (FALSE);	
}

int		expand(char **arg, int i, int dquote)
{
	int		j;

	j = i + 1;
	if (dquote == FALSE && ((*arg)[j] == '\'' || (*arg)[j] == '"'))
	{
		ft_memmove(&((*arg)[i]), &((*arg)[j]), ft_strlen(*arg) - i);
		return (i);
	}
	else if ((*arg)[j] == '?')
		expand_resvar(arg, &j);
	else if (envvar_authorized_character((*arg)[j], TRUE) == TRUE)
	{
		j++;
		while (envvar_authorized_character((*arg)[j], FALSE) == TRUE)
			j++;
		expand_envvar(arg, i, &j);
	}
	i = j;
	return (i);
}

int		escape_char(char **s, int i, int boolean_value)
{
	ft_memmove(&(*s)[i], &(*s)[i + 1], ft_strlen(*s) - i);
	return (boolean_value);
}

int		interpret_arg(char **s)
{
	t_boolean sq;
	t_boolean dq;
	int i;

	i = 0;
	sq = FALSE;
	dq = FALSE;
	while (*s && i > -1 && (*s)[i])
	{
		if (!sq && !dq && (*s)[i] == 92)
			i += escape_char(s, i, TRUE);
		else if (!sq && dq && (*s)[i] == 92 && ((*s)[i + 1] == '\\'
				|| (*s)[i + 1] == '$' || (*s)[i + 1] == '\"'))
			i += escape_char(s, i, TRUE);
		else if (!sq && (*s)[i] == '$')
			i = expand(s, i, dq);
		else if (!dq && (*s)[i] == 39) 
			sq = escape_char(s, i, !sq);
		else if (!sq && (*s)[i] == 34)
			dq = escape_char(s, i, !dq);
		else
			i++;
	}
	i = sq == TRUE || dq == TRUE || i == -1 ? 1 : 0;
	return (i);
}

int		interpreter(char **args)
{
	int i;
	int r;
	
	r = 0;
	i = 0;
	while (args && r != -1 && args[++i])
		r = interpret_arg(&(args[i]));
	return (r);
}
