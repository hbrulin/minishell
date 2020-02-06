/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmouhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 10:57:35 by pmouhali          #+#    #+#             */
/*   Updated: 2020/02/06 13:30:38 by pmouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "libft.h"

# define TRUE  1
# define FALSE 0

typedef short int t_boolean;

char **env;

int	run_dmc(char **args);
int run(char *s);
char **copy_tab(char **envp);
size_t	ft_tablen(char **arr);
int		ft_is_space(char c);
char **parse_arg(char *args);


#endif
