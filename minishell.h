/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:27:50 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/11 18:45:57 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "libft.h"
# include "printf.h"
# include <dirent.h>
# include <sys/stat.h>

# define TRUE  1
# define FALSE 0

typedef short int t_boolean;

typedef int	t_ret;
t_ret	g_ret;

t_list *env;
t_list *export;

int		run_dmc(char **args);
int		parse_cmds(char *s);
int		parsexec(char *cmd);
char	**parse_arg(char *args);
int		ft_exit(char **args);
int		ft_env(char **args);
int		ft_pwd(char **args);
int		ft_execve(char **args);
char	*get_var(t_list *lst, char *key);
t_list	*del_var(t_list *lst, char *key);
int		ft_cd(char **args);
int		ft_access(char *path);
void	signal_handler(int n);
int		is_forking(int val);
int		ft_error(char *msg, int ret, char *befree, void *param);
int		ft_export(char **args);
t_list	*ft_tab_to_list_custom(t_list **lst, char **tab);
int		ft_lstiter_custom(t_list *lst, char *arg, int (*f)(void *, void *, int));
int		ft_unset(char **args);
int		set_var(t_list *lst, char *key, char *value);
int		interpreter(char **args);
int		envvar_authorized_character(char c, int first_char);
int		set_var_full(t_list *lst, char *key, char *value);
void	ft_lstprint_export(t_list *lst);

#endif
