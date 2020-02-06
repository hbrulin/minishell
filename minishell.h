/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:23:48 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 13:24:26 by hbrulin          ###   ########.fr       */
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

# define TRUE  1
# define FALSE 0

typedef short int t_boolean;

typedef char **t_env;

int	run_dmc(char **args);
int parse_cmds(char *s);
char **parse_arg(char *args);


#endif
