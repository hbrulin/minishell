/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmouhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 12:45:04 by pmouhali          #+#    #+#             */
/*   Updated: 2020/02/08 12:45:09 by pmouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "libft.h"
#include "printf.h"
# include <dirent.h>

# define TRUE  1
# define FALSE 0

typedef short int t_boolean;

typedef char **t_env;
typedef int	t_ret;
t_env	g_env;
t_ret	g_ret;

int	run_dmc(char **args);
int parse_cmds(char *s);
char **parse_arg(char *args);
int		ft_exit(char **args);
int		ft_env(char **args);
int		ft_pwd(char **args);
int		ft_execve(char **args);
char    *get_var(char *key);
void    set_var(char *key, char *value);
int		ft_cd(char **args);


#endif
