/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:11:01 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/05 17:33:34 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "libft.h"

char **env;

int	run_dmc(char **args);
int run(char *s);
char **copy_tab(char **envp);
size_t	ft_tablen(char **arr);
int		ft_is_space(char c);
char **parse_arg(char *args);


#endif
