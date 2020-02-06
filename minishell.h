/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:11:01 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/05 17:39:10 by pmouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "libft.h"

# define TRUE  1
# define FALSE 0

typedef short int t_boolean;

char **env;

int	run_dmc(char **args);
char **parser(char *input);
char **copy_tab(char **envp);


#endif
