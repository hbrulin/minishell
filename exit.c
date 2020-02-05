
int		parse_exit(char *args)
{
	char *exit;
	int i = 4;
	exit = ft_strtrim(args, " ");
	int len = ft_strlen(exit);
	if (len == i)
		return(0);
	else if (ft_isprint(exit[i]) && !(ft_is_space(exit[i])))
	{
		ft_putstr("minishell: command not found\n"); //ajouter printf ici
		free(exit);
		return(1);
	}
	while (ft_is_space(exit[i]) && exit[i])
		i++;
	if (ft_isprint(exit[i]))
	{
		ft_putstr("minishell: exit: unknown argument\n"); //ajouter printf ici pour l'argment inconnu
		free(exit);
	}
	return(0);
}
