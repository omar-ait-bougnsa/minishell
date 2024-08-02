#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
char	*ft_strdup(char *str)
{
	int		i;
	char	*cp;

	i = 0;
	if (str == NULL)
		return (NULL);
	cp = malloc(ft_strlen(str) + 1);
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
int	count_cmd(t_lexer *lexer)
{
	int	cont;

	cont = 0;
	while (lexer)
	{
		if (lexer->token == pipe1)
			cont++;
		lexer = lexer->next;
	}
	return (cont);
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
void	apend_to_file(char *str, t_token token, t_file **file)
{
	t_file	*newfile;

	newfile = ft_calloc(sizeof(t_file), 1);
	if (newfile == NULL)
		return ;
	newfile->file = str;
	if (token == inredire)
		newfile->infile = 1;
	else if (token == outredire)
		newfile->outfile = 1;
	else if (token == herduc)
		newfile->herdoc = 1;
	else if (token == apenred)
		newfile->apend = 1;
	ft_lstadd_back1(file, newfile);
}
void	apend_to_data(t_data **data, t_file **file, char ***cmd)
{
	t_data	*newdata;
	t_data	*tmp;

	newdata = ft_calloc(sizeof(t_data), 1);
	if (newdata == NULL)
		return ;
	newdata->cmd = *cmd;
	newdata->file = *file;
	*file = NULL;
	tmp = *data;
	if (*data)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = newdata;
	}
	else
		*data = newdata;
	*cmd = NULL;
}

int	count_str(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}
char	**ft_addstring(char **str, char *newstr)
{
	char	**p;
	int		cont;
	int		i;

	i = 0;
	cont = count_str(str);
	p = ft_calloc(sizeof(char *), cont + 2);
	if (p == NULL)
		return (NULL);
	while (i < cont)
	{
		p[i] = ft_strdup(str[i]);
		i++;
	}
	p[i++] = ft_strdup(newstr);
	i = 0;
	while (str && str[i])
		free(str[i++]);
	if (str)
		free(str);
	return (p);
}
t_data	*ft_parsing(t_lexer *lexer, char **env)
{
	t_data	*data;
	char	**cmd;
	t_file	*file;

	cmd = NULL;
	data = NULL;
	(void)env;
	if (lexer == NULL)
		return (NULL);
	file = NULL;
	while (lexer)
	{
		if (lexer->token == word && lexer->prev == NULL)
			cmd = ft_addstring(cmd, lexer->data);
		else if (lexer->token == word && lexer->prev->token == inredire)
			apend_to_file(lexer->data, inredire, &file);
		else if (lexer->token == word && lexer->prev->token == outredire)
			apend_to_file(lexer->data, outredire, &file);
		else if (lexer->token == word && lexer->prev->token == herduc)
			apend_to_file(lexer->data, herduc, &file);
		else if (lexer->token == word && lexer->prev->token == apenred)
			apend_to_file(lexer->data, apenred, &file);
		else if (lexer->token == pipe1)
			apend_to_data(&data, &file, &cmd);
		else if (lexer->token == word)
			cmd = ft_addstring(cmd, lexer->data);
		lexer = lexer->next;
	}
	apend_to_data(&data, &file, &cmd);
	free_lexer(lexer);
	return (data);
}
