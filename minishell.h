/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:45:48 by omar              #+#    #+#             */
/*   Updated: 2024/09/03 16:09:53 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define WO_RD 1
# define PI_PE 2
# define IN_RED 3
# define OUT_RED 4
# define HE_RDUC 5
# define AP_END 6

# define FG_GREEN "\001\033[36m\002"
# define FG_YELLOW "\001\033[32m\002"

typedef struct t_file
{
	char			*file;
	int				infile;
	int				outfile;
	int				herdoc;
	int				apend;
	int				ambiguous;
	int				fd[2];
	int				expand;
	struct t_file	*next;
}					t_file;

typedef struct t_lexer
{
	char			*data;
	int				type;
	struct t_lexer	*next;
	struct t_lexer	*prev;
}					t_lexer;
typedef struct t_var
{
	char			**cmd;
	t_file			*file;
	t_lexer			*new;
	int				sinqot;
	int				dobqot;
	int				i;
	int				j;
	char			*var;
	char			**newstr;
	int				n;
	char			*s;
	int				flg;
}					t_var;
typedef struct s_env
{
	char			**env;
	char			*var;
	char			*value;
	char			*pwd;
	int				egnor;
	int				exit_status;
	struct s_env	*next;
}					t_env;
typedef struct t_var_us
{
	int				cont_cmd;
	char			**path;
	char			*pth;
	int				fd;
	int				infd;
	int				outfd;
	int				**pipe;
	int				*id;
	int				i;
	int				n;
	t_env			*envp;
}					t_var_us;

typedef struct t_data
{
	char			**cmd;
	t_file			*file;
	struct t_data	*next;
}					t_data;

typedef struct t_var_free
{
	int				exit_s;
	t_env			*env;
	t_data			*data;
	t_var_us		*var;
	int				flg;
}					t_var_free;

char				**ft_split(char *str, char c);
int					count_str(char **str);
t_data				*ft_parsing(t_lexer *lexer, t_env *envp);
int					ft_strlen(char *str);
int					syntax_error(t_lexer **lexer);
char				*ft_strsrch(char *str, char c);
char				*apend_char_str(char *str, char c);
void				apend_in_struct(t_lexer **lexer, char *str, int type);
void				ft_lstadd_back(t_lexer **lst, t_lexer *new);
int					ft_token(char c, int *singl, int *doubl);
int					get_next_qout(char *str);
char				*ft_strncpy(char *dest, char *src, int size);
void				ft_lexer(char *len, t_lexer **lexer);
char				**ft_catstr(char **str, char **str1);
char				*ft_strncpy(char *dest, char *src, int size);
int					count_list(t_data *data);
void				*ft_calloc(size_t count, size_t size);
void				free_lexer(t_lexer *lexer);
char				*ft_strdup(char *str);
char				**ft_split_it(char *str);
char				*ft_itoa(int nb);
char				**ft_addstring(char **str, t_lexer *lexer, t_env *envp);
int					ft_isalnum(int c);
char				*expending_herd(char *str, t_env *envp);
int					ft_atoi(char *str);
int					is_whitespace(char c);
char				**ft_catstr(char **str, char **str1);
int					print_error(t_lexer **lexer, char *str, char *str1);
void				f(int sig);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_lstadd_backenv(t_env **env, t_env *new);
void 				check_word_expand(char *str,t_var *var);
// exicutiom ------------------
void				ft_execution(t_data **data, char **env, t_env **envp);
int					check_file(t_data *data, t_var_us *var);
int					ft_strchr(const char *s, int c);
char				*check_path(t_var_us var, t_data *data);
void				execut_comand(t_data **data, char **env, t_env **envp);
void				ft_setenv(char *env, t_env **envp);
char				*ft_getenv(t_env *env, char *str);
void				*ft_memcpy(void *dest, const void *src, size_t size);
void				ft_lstadd_backenv(t_env **env, t_env *new);
int					ft_export(t_data *data, t_env **env);
int					ft_strcmp(char *s1, char *s2);
int					ft_unset(t_data *data, t_env **envp);
int					execut_buildin(t_data *data, t_env **envp);
int					check_singcmd_build(t_data *data, t_env **envp);
int					check_cmd_build(t_data *data, t_env **envp, t_var_us var);
void				ft_free1(char **str);
void				free_data(t_data *data);
char				*ft_getvar(char *str);
char				*ft_strjoinn(char *s1, char *ss2);
int					ft_isalpha(int c);
char				**ft_expending_word(char *str, t_env *envp, int flg);
void				ft_exit(t_data *data, t_env *envp);
int					ft_herdoc(t_data *data, t_env *envp);
void				free_envp(t_env *envp);
int					ft_isdigit(int c);
int					ft_cd(t_data *data, t_env *env);
char				*skip_char(char *s, char c);
int					execut_buildin(t_data *data, t_env **envp);
int					ft_printf(char *s1, char *s2, char *s3);
int					ft_printf1(char *s1, char s2, char *s3);
void				handle_child(t_data *data, t_var_us var, char **env,
						t_env **envp);
int					ft_echo(t_data *data);
int					ft_env(t_data *data, t_env *evnp);
void				free_file(t_file *file);
void				free_var(t_var_us *var);
void				check_status(int status, t_env *envp);
void				child_handler1(int signum);
void				child_handler(int signum);
void				handle_signal1(int sig);
void				ft_execve(t_data *data, t_var_us var, t_env *envp,
						char **env);
char				**get_envp(t_env *envp, char **env);
void				check_file1(t_data *data, t_var_us *var);
void				apend_to_file(t_lexer *lexer, int type, t_file **file,
						t_env *envp);
void				set_env(char **env, t_env **envp);
void				sort_print(t_env *env);

#endif