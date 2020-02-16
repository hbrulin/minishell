/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helenebrulin <helenebrulin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:44:02 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/16 15:32:14 by helenebruli      ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

# define TRUE  1
# define FALSE 0

# define SIGINT_ERR 130
# define SIGQUIT_ERR 131

//#define CMD_NOT_FOUND(cmd)	ft_printf_fd(2, "minishell: %s: command not found\n", (cmd));
# define	CMD_NOT_FOUND	"minishell: %s: command not found\n"
//# define	CMD_FAIL_EXEC	"minishell: %s: command could not be executed\n"
//# define	PERM_DENIED		"minishell: %s: permission denied\n"
//# define	FATAL_ERROR		"minishell: fatal error: %s\n"
//# define	MALLOC_FAIL		"minishell: fatal error: memory was not allocated properly\n"
# define	MANY_ARGS		"minishell: %s: too many arguments\n"
# define	NO_ARG			"minishell: %s: not enough arguments\n"
# define	NO_FILE			"minishell: cd: %s: No such file or directory\n"
# define	EXIT_NUM		"minishell: exit: %s: numeric argument required\n"
# define	INVALID_ID_X	"minishell: export: %s: not a valid identifier\n"
# define	INVALID_ID_U	"minishell: unset: %s: not a valid identifier\n"
# define	SYNTAX_ERR		"minishell: syntax error near unexpected token\n"

typedef struct s_parse_tools
{
    int i;
	int j;
	int open;
	char quote;
}              t_parse_tools;

typedef short int t_boolean;
typedef int	(*t_builtin_fc)(char **args);

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
int		ft_echo(char **args);
int		ft_execve(char *path, char **args);
char	*get_var(t_list *lst, char *key);
t_list	*del_var(t_list *lst, char *key);
int		ft_cd(char **args);
int		ft_access(char *path);
void	signal_handler(int n);
int		is_forking(int val);
int		ft_export(char **args);
t_list	*ft_tab_to_list_custom(t_list **lst, char **tab);
int		ft_lstiter_custom(t_list *lst, char *arg, int (*f)(void *, void *, int));
int		ft_unset(char **args);
int		set_var(t_list *lst, char *key, char *value);
int		interpreter(char **args);
int		envvar_authorized_character(char c, int first_char);
int		set_var_full(t_list *lst, char *key, char *value);
void	ft_lstprint_export(t_list *lst);
int		ft_error_tab(char *msg, int ret, char **befree, void *param);
char    *try_path(char *path, int *error);
char	*tryent_dirs(const char *dirs, const char *entry, int *err);
int		redirect(char **args);
int		run_dmc_pipes(char **args);
int		ft_error(char *msg, char *befree, char **tab_free, void *param);
int		ft_strerror(char *befree, char **tabfree, void *param, void *param2);
char    **ft_rmfd(char **args);

#endif
