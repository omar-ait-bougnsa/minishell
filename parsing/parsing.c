#include "minishell.h"

int ft_strlen (char *str)
{
    int i;
    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}
char *ft_strdup(char *str)
{
    int i;
    char *cp;

    i = 0;
    if (str == NULL)
        return (NULL);
    cp = malloc (ft_strlen(str) + 1);
    if (cp == NULL)
        return (NULL);
    while (str[i])
    {
        cp[i] = str[i];
        i++;
    }
    cp[i] = '\0';
    return (cp);
}
int count_cmd (t_lexer *lexer)
{
    int cont;
    cont = 0;
    while (lexer)
    {
        if (lexer->token  == pipe1)
            cont++; 
        lexer = lexer->next;
    }
    return (cont);
}
char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*p;

	j = 0;
	i = 0;
    if (!s2)
        return(s1);
	if (s1 == NULL)
	{
		p = malloc(ft_strlen(s2) + 1);
		while (s2[i])
        {
            p[i] = s2[i];
            i++;
        }
        p[i] = '\0';
		return (p);
	}
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (p == NULL)
		return (0);
	while (s1[j])
		p[i++] = s1[j++];
	j = 0;
	p[i] = ' ';
	i++;
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	free(s1);
	return (p);
}
void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count != 0 && size > SIZE_MAX / count)
		return (0);
	p = malloc(count * size);
	if (p == NULL)
		return (NULL);
	memset(p, 0, count * size);
	return (p);
}
void	ft_lstadd_back1(t_file **file, t_file *new)
{
	t_file	*tmp;

	if (!file || !new)
		return ;
	if (*file)
	{
        tmp = *file;
		while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new;
	}
	else
		*file = new;
}
void apend_to_file (char *str,t_token token,t_file **file)
{
    t_file *newfile;
    int len;

    newfile = ft_calloc (sizeof (t_file),1);
    if (newfile == NULL)
        return;
    newfile->file = str;
    if (token == inredire)
        newfile->infile = 1;
    else if (token == outredire)
        newfile->outfile = 1;
    else if (token == herduc)
        newfile->herdoc = 1;
    else if (token == apenred)
        newfile->apend = 1;
    ft_lstadd_back1(file,newfile);

}
void apend_to_data (t_data **data,t_file **file,char **cmd)
{
    t_data *newdata;
    t_data *tmp;
    newdata = ft_calloc(sizeof(t_data),1);
    if (newdata == NULL)
        return;
    newdata->cmd = ft_strdup (*cmd);
    newdata->file = *file;
    *file = NULL;
    tmp = *data;
    if(*data) {
         while(tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = newdata;
        }
    else
        *data = newdata;
    free (*cmd);
    *cmd = NULL;
}
t_data *ft_parsing (t_lexer *lexer, char **env)
{
    t_data *data;
    char *cmd;
    cmd = NULL;
    data = NULL;
    t_file *file;
    if (lexer == NULL)
        return (NULL);
    int cont = count_cmd (lexer);
    file = NULL;
    while (lexer)
    {
        if (lexer->token == word && lexer->prev == NULL)
            cmd = ft_strjoin(cmd,lexer->data);
        else if (lexer->token == word && lexer->prev->token == inredire)
                apend_to_file (lexer->data,inredire,&file);
        else if (lexer->token == word && lexer->prev->token == outredire)
                apend_to_file (lexer->data,outredire,&file);
        else if (lexer->token == word && lexer->prev->token == herduc)
                apend_to_file (lexer->data,herduc,&file);
        else if (lexer->token == word && lexer->prev->token == apenred)
                apend_to_file (lexer->data,apenred,&file);
        else if (lexer->token == pipe1)
                apend_to_data (&data,&file,&cmd);
        else if (lexer->token == word)
            cmd = ft_strjoin(cmd,lexer->data);
        lexer = lexer->next;
    }
    apend_to_data (&data,&file,&cmd);
    return (data);
}
