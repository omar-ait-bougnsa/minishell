#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>

typedef struct t_file
{
    char *file;
    int infile;
    int outfile;
    int herdoc;
    int apend;
    struct t_file *next;
}t_file;

typedef enum token
{
    word,
    pipe1,
    inredire,
    outredire,
    herduc,
    apenred,
    error,
}t_token;

typedef struct t_lexer
{
    char *data;
    t_token token;
    struct t_lexer *next;
    struct t_lexer *prev;
}t_lexer;
typedef struct t_var
{
    int sinqot;
    int dobqot;
    int i;
    int j;
    char *var;
    char *newstr;
} t_var;
typedef struct t_var_us
{
    char **path;
    char *pth;
    int fd;
    int infd;
    int outfd;
    int **fd1;
    int *id;
} t_var_us;
typedef struct s_env
{
    char *var;
    char *value;
    struct s_env *next;
}t_env;

typedef struct t_data
{
    char **cmd;
    char *oldpwd;
    char *newpwd;
    t_file *file;
    struct t_data *next;
}t_data;

char  **ft_split (char *str,char c);
t_data *ft_parsing (t_lexer *lexer, char **env);
int ft_strlen (char *str);
int syntax_error(t_lexer **lexer);
void ft_execution(t_data *data,char **env);
char *ft_strsrch(char *str,char c);
char	*ft_expending(t_lexer *lexer, char *str, t_token *token,t_env *envp);
char *apend_char_str (char *str,char c);
void	apend_in_struct(t_lexer **lexer, char *str, t_token token,t_env *envp);
void ft_lstadd_back(t_lexer **lst, t_lexer *new);
int ft_token(char *len,int i,int *singl,int *doubl);
int get_next_qout (char *str);
char *ft_strncpy (char *dest,char *src,int size);
void	lexer_phase(char *len, t_lexer **lexer,t_env *envp);
char *remove_qout (char *str);
char *ft_strncpy (char *dest,char *src,int size);
int	count_list(t_data *data);
void	*ft_calloc(size_t count, size_t size);
void free_lexer(t_lexer *lexer);
char	*ft_strdup(char *str);
//exicutiom ------------------
void	check_file(t_data *data, t_var_us *var);
char	*check_path(t_var_us var, char **cmd);
void execut_comand(t_data *data,char **env);
void ft_setenv(char **env,t_env **envp);
char *ft_getenv (t_env *env,char *str);
void	*ft_memcpy(void *dest, const void *src, size_t size);
#endif
