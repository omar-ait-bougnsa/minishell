#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

// -lreadline
// void full_data (char *word,t_data *data)
// {
//     int i;
//     char **words;

//     words = ft_split (word,' ');
//     while (words[i])
//     {
//     }
// }
char *ft_strncpy (char *dest,char *src,int size)
{
    int i;
    i = 0;

    while (i < size)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}
char *ft_strsrch(char *str,char c)
{
    int i;

    i = 0;
    if (!str)
        return (NULL);
    while (str[i])
    {
        if (str[i] == c)
            return (&str[i]);
        i++;
    }
    return (NULL);
}
int check_quote (char *str)
{
    int i;
    i = 0;
    int sinqot;
    int dbqot;
    sinqot = 1;
    dbqot = 1;
    while (str[i])
    {
        if (str[i] == '\"' && sinqot == 1)
            dbqot *= -1;
        if (str[i]== '\'' && dbqot == 1)
            sinqot *= -1;
        i++;
    }
    if (dbqot == -1 || sinqot == -1)
        return (0);
    return (1);
}
int check_char_in_str(char c,char *str)
{
    int i;
    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (0);
        i++;
    }
    return (1);
}
int get_next_qout (char *str,char c)
{
    int i;

    int sinqot;
    int dobqot;

    i = 0;
    sinqot = 1;
    dobqot =  1;
    while (str[i])
    {
        if (str[i] == '\'' && dobqot == 1)
        {
            sinqot *= -1;
        }
        if (str[i] == '\"' && sinqot == 1)
        {
            dobqot *= -1;
        }
        if (sinqot == 1 && dobqot == 1 && !check_char_in_str(str[i],"<> |\t\v"))
            return (i);
        i++;
    }
    return (i);
}

int ft_token(char *len,int i,int *singl,int *doubl)
{
    if (len[i] == '\'' && *doubl != -1)
            *singl *= -1;
    if (len[i] == '\"' && *singl != -1)
        *doubl *= -1;
    if (len[i] == '\'' && (len[i + 1] == ' ' || len[i + 1] == '\t'))
        return (0);
    if (len[i] == '\"' && (len[i + 1] == ' ' || len[i + 1] == '\t'))
        return (0);
    if (len[i] == '>' && (*singl != -1 && *doubl != -1))
        return (0);
    if (len[i] == '<' && (*singl != -1 && *doubl != -1))
        return (0);
    if (len[i] == '|' && (*singl != -1 && *doubl != -1))
        return(0);
    if (len[i] == 32  && (*singl != -1 && *doubl != -1))
        return (0);
    if (len[i] == '\t' && (*singl != -1 && *doubl != -1))
        return (0);
    else
        return (1);
}

void ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
    t_lexer *temp;

    if (!lst || !new)
        return ;
    if (*lst)
    {
        temp = *lst;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new;
        new->prev = temp;
    }
    else
        *lst = new;
}
char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}
int ft_check_singl_coutch(char *str,char *newstr)
{
    int i;
    int n;

    n = 1;
    i = 0;
    while (str[i])
    {
        if (str[i] == newstr[0])
            return (n);
        if (str[i] == '\'')
            n *= (-1);
        i++;
    }
    return (n);
}
int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
char *apend_char_str (char *str,char c)
{
    int i;
    char *new;
    i = 0;
    if (str == NULL)
    {
        new = malloc (2);
        if (new == NULL)
            return (NULL);
        new[0] = c;
        new[1] = '\0';
        return (new);
    }
    while (str[i])
        i++;
    new = malloc(i + 2);
    if (new ==NULL)
        return(NULL);
    i = 0;
    while (str[i])
    {
        new[i] = str[i];
        i++;
    }
    new[i++] = c;
    new[i] = '\0';
    free (str);
    return (new);
}
char *ft_expending_word(char *str)
{
    int i;
    int n;
    int j;

    i = 0;
    n = 1;
    char *newstr;
    char *path;
    char *var;
    j = -1;
    newstr = NULL;
    while (str[i])
        {
            var = NULL;
            if (str[i] == '\'')
                n *= (-1);
            if (str[i] == '$' && n == 1  && ft_isalnum(str[i + 1]))
                {
                    i++;
                    while (str[i] && ft_isalnum(str[i]))
                        {
                            var = apend_char_str (var,str[i]);
                            i++;
                        }
                }
            else if (str[i] != '\0')
                {
                    newstr = apend_char_str (newstr,str[i]);
                    i++;
                }
            if (var != NULL)
                {
                    path = getenv(var);
                    free (var);
                    while (path && path[++j])
                        newstr = apend_char_str (newstr,path[j]);
                }
                
        }
    return (newstr);
}

char *remove_qout (char *str)
{
    int i;
    int sinqot;
    int dobqot;
    char *newstr;
    i = 0;
    sinqot = 1;
    dobqot = 1;
    newstr = NULL;
    if (!str)
        return(NULL);
    while (str[i])
    {
        if (str[i] == '\'' && dobqot == 1)
            sinqot *= (-1);
        if (str[i] == '\"' && sinqot == 1)
            dobqot *= (-1);
        if (str[i] == '\'' && dobqot == 1)
            i++;
        else if(str[i] == '\"' && sinqot == 1)
            i++;
        else
        {
            newstr = apend_char_str(newstr,str[i]);
            i++;
        }
    }
    free (str);
    return (newstr);
}


char *ft_expending(t_lexer *lexer,char *str)
{
    char *newstr;
    if (!lexer)
        newstr = ft_expending_word (str);
    else 
    {
        while (lexer->next != NULL)
            lexer = lexer->next;
        if (lexer->token != herduc)
                newstr = ft_expending_word (str);
        else
           newstr = str;
    }
    newstr = remove_qout (newstr);
    return (newstr);
}

void apend_in_struct (t_lexer **lexer,char *str,t_token token)
{
   t_lexer *new_lexer;
   int len;
   len = ft_strlen (str);
        str = ft_expending(*lexer,str);
   if (token == inredire && len == 2)
        token = herduc;
    else if (token == outredire && len == 2)
        token = apenred;
   new_lexer = malloc (sizeof(t_lexer));
   if (new_lexer == NULL)
        return;
    new_lexer->data = str;
    new_lexer->token = token;
    new_lexer->next = NULL;
    new_lexer->prev = NULL;
    ft_lstadd_back(lexer,new_lexer);
}

void lexer_phase(char *len,t_lexer **lexer)
{
    int i;
    int b;
    char *str;
    str = NULL;
    int singl;
    int doubl;
    i = 0;
   *lexer = NULL;
    while (len[i])
    {
        b = 0;
        if (len[i] == '\"' || len[i] == '\'')
        {
            b = get_next_qout (&len[i],len[i]);
            str = malloc (b + 1);
           if (str == NULL)
                return;
            ft_strncpy(str,&len[i],b);
            apend_in_struct (lexer,str,word);
            i += b;
        }
       else if (len[i] == '>')
        {
            b = i;
            while (len[b] == '>')
                b++;
            str = malloc (b - i + 1);
           if (str == NULL)
                return;
            ft_strncpy(str,&len[i],b - i);
            apend_in_struct (lexer,str,outredire);
            i+=b - i;
        }
        else if (len[i] == '<')
        {
            b = i;
            while (len[b] == '<')
                b++;
            str = malloc (b - i + 1);
           if (str == NULL)
                return;
            ft_strncpy(str,&len[i],b - i);
            apend_in_struct (lexer,str,inredire);
            i+= b - i;
        }
       else if (len[i] == '|')
        {
            b = i;
            while (len[b] == '|')
                b++;
            str = malloc (b - i + 1);
           if (str == NULL)
                return;
            ft_strncpy(str,&len[i],b - i);
            apend_in_struct (lexer,str,pipe1);
            i += b - i;
        }
        else if (len[i] == ' ' || len[i] == '\t')
            i++;
        else
        {
            b = i;
            singl = 1;
            doubl = 1;
            while (len[b] && ft_token (len,b,&singl,&doubl))
                b++;
            if (len[b] == '\'' || len[b] == '\"')
                b++;
            str = malloc (b - i + 1);
           if (str == NULL)
                return;
           str = ft_strncpy(str,&len[i],b - i);
            apend_in_struct (lexer,str,word);
            i += b - i;
        }
    }
    syntax_error(lexer);
}
int main (int ac,char **av,char **env)
{
    int i;
    i = 0;
    int j;
    t_data *data;
    t_lexer *lexer;
    while(1)
    {
        char *len = readline ("minshell $>");
        if (!check_quote(len))
        {
            printf("syntax error\n");
        }
        else 
        {
        lexer_phase(len,&lexer);
        data = ft_parsing (lexer,env);
        ft_execution(data,env);
        while (data)
        {
            printf("------------------------------------\n");
            printf ("command is %s\n",data->cmd);
            printf("------------------------------------\n");
            if (data->file)
            {
                while (data->file)
                {
                    if (data->file->infile == 1)
                        printf("infile is  %s\n",data->file->file);
                    else if (data->file->herdoc == 1)
                        printf("herdoc is %s\n",data->file->file);
                    else if (data->file->apend == 1)
                        printf("apend is %s\n",data->file->file);
                    else
                        printf("outfile is  %s\n",data->file->file);
                    data->file = data->file->next;
                printf("------------------------------------\n");
                }
            }
            printf ("other pipe______________________________________|\n");
            data = data->next;
        }
        }
        add_history(len);
    }
}
