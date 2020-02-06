/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:11:01 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/06 12:08:19 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "libft.h"
#include "printf.h"

typedef char **t_env;

int	run_dmc(char **args);
int run(char *s);
char **parse_arg(char *args);


#endif
