/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:44:02 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/11 18:38:50 by hbrulin          ###   ########.fr       */
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
# include <stdio.h>

# define TRUE  1
# define FALSE 0

# define SIG_CODE 128
# define ESYNTAX 258
# define ARG_MAX 131072
# define ERROR -1

# define STDIN 0
# define STDOUT 1
# define CHILD 0
# define PIPEIN 0
# define PIPEOUT 1

# define CMD_NOT_FOUND	"minishell: %s: command not found\n"
# define MANY_ARGS		"minishell: %s: too many arguments\n"
# define NO_ARG			"minishell: %s: not enough arguments\n"
# define NO_FILE		"minishell: %s: No such file or directory\n"
# define NO_FILE_LS		"ls: : No such file or directory\n"
# define EXIT_NUM		"minishell: exit: %s: numeric argument required\n"
# define INVALID_ID_X	"minishell: export: %s: not a valid identifier\n"
# define INVALID_ID_U	"minishell: unset: %s: not a valid identifier\n"
# define SYNTAX_ERR		"minishell: syntax error near unexpected token\n"
# define RNO_FILE		"minishell: %s: No such file or is a directory\n"
# define RNO_CREA		"minishell: %s: File could not be created\n"

typedef short int	t_boolean;
typedef int			(*t_builtin_fc)(char **args);

typedef size_t		t_size;
typedef size_t		t_index;
typedef	int			t_fd;
typedef pid_t		t_pid;
typedef int			t_status;

typedef enum		e_dir
{
	NO_REDIR,
	INPUT,
	OUTPUT,
	APPEND
}					t_dir;

typedef struct		s_redir
{
	t_dir		direction;
	char		*name;
}					t_redir;

typedef struct		s_cmd
{
	char		*path;
	char		**arguments;
	int			pipe_flag;
	t_redir		**redirs;
}					t_cmd;

typedef struct		s_parse_tools
{
	int		i;
	int		j;
	int		open;
	char	quote;
	char	*tmp;
	int		done;
	int		count;
}					t_parse_tools;

typedef struct		s_interp_tools
{
	t_boolean	sq;
	t_boolean	dq;
	int			i;
	char		*s;
}					t_interp_tools;

typedef struct		s_pipe_tools
{
	char	**a_cmd;
	int		i;
	int		adv;
	int		j;
	int		k;
	int		len;
	t_cmd	**cmd;
}					t_pipe_tools;

typedef	struct		s_redir_tools
{
	int		i;
	int		len;
	int		j;
}					t_redir_tools;

typedef	struct		s_rm_var_tools
{
	char	**cpy;
	char	*key;
	char	*tmp;
	int		i;
	int		j;
	int		k;
	int		l;
	int		count;
}					t_rm_var_tools;

typedef int			t_ret;
t_ret				g_ret;

t_list				*g_env;
t_list				*g_export;

int					run_dmc(char **args);
int					parse_cmds(char *s);
int					parsexec(char *cmd);
char				**parse_args(char *args);
int					ft_exit(char **args);
int					ft_env(char **args);
int					ft_pwd(char **args);
int					ft_echo(char **args);
int					ft_execve(char *path, char **args);
char				*get_var(t_list *lst, char *key);
t_list				*del_var(t_list *lst, char *key);
int					ft_cd(char **args);
int					ft_access(char *path);
void				signal_handler(int n);
int					is_forking(int val);
int					ft_export(char **args);
t_list				*ft_tab_to_list_custom(t_list **lst, char **tab);
int					ft_lstiter_custom(t_list *lst, char *arg);
int					ft_unset(char **args);
int					set_var(t_list *lst, char *key, char *value);
int					interpreter(char **args);
int					envvar_authorized_character(char c, int first_char);
int					set_var_full(t_list *lst, char *key, char *value);
int					ft_lstprint_export(t_list *lst);
int					ft_error_tab(char *msg, int ret, char **befree,
						void *param);
char				*try_path(char *path);
char				*build_path(const char *dirs, const char *entry);
char				**redirect(char **args);
int					handle_pipes(char **good_var);
int					ft_error(char *msg, char *befree, char **tab_free, void
						*param);
int					ft_strerror(char *befree, char **tabfree, void *param,
						void *param2);
char				**ft_rmfd(char **args, char **sub);
void				set_quote(char c, t_parse_tools *t);
int					check_error_syntax(char **args);
int					ft_is_operand(char c);
int					check_operand(char *s);
int					ft_tab_chr_i_custom(char **tab);
void				set_io(int i);
int					path_exec(char **sub);
int					expand(char **arg, int i, int dquote);
int					add_node(t_parse_tools *t, t_list **list);
int					ft_ret_errno(char *befree, char **tabfree, void *param);
char				**copy_tab_void(char **tab);
int					ls_part(char **args);
int					ft_count_back(char *s, int i);
int					check_error_cmds(char *s);
void				set_escape(t_parse_tools *t, char *s);
int					set_node(t_list **list, char *s, t_parse_tools *t,
						int flag);
int					set_node2(t_list **list, char *s, t_parse_tools *t,
						int flag);
char				**rm_wrong_var(char **args);
t_redir				**build_redir(char **a_cmd);
char				**ft_rmfd_pipes(char **args);
t_status			execute_cmds(t_cmd **cmds, char **env);
void				create_pipeline(t_cmd **cmds, t_cmd **pipeline);
t_size				count_pipes(t_cmd **cmds);
t_status			ret_status(t_pid last_pid);
void				apply_redirs(t_redir **redirs);
void				free_redirs(t_redir **redirs);
void				free_t_cmd(t_cmd **cmd);
int					count_pip(char **args);
char				**get_cmd(char **args, int adv, int i, int flag);

#endif
