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
}t_token;

typedef struct t_lexer
{
    char *data;
    t_token token;
    struct t_lexer *next;
    struct t_lexer *prev;
}t_lexer;

typedef struct t_var_us
{
    char **path;
    char *pth;
    int fd;
    int infd;
    int outfd;
} t_var_us;

typedef struct t_data
{
    char *cmd;
    t_file *file;
    struct t_data *next;
}t_data;

char  **ft_split (char *str,char c);
t_data *ft_parsing (t_lexer *lexer, char **env);
int ft_strlen (char *str);
int syntax_error(t_lexer **lexer);
char	*check_path(t_var_us *var, char **cmd);
void ft_execution(t_data *data,char **env);
char *ft_strsrch(char *str,char c);
#endif
