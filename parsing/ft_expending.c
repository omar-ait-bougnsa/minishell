#include "minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

char	*expend_it(char *var, char *newstr,t_env *envp)
{
	int		j;
	char	*path;

	j = -1;
	path = ft_getenv(envp,var);
	free(var);
	while (path && path[++j])
		 newstr = apend_char_str(newstr, path[j]);
	return (newstr);
}

char	*add_to_str(char *str, t_var var, int *i)
{
	if (str[*i] == '$' && var.sinqot == 1 && var.dobqot == 1 && (str[*i
			+ 1] == '\"' || str[*i + 1] == '\''))
		*i += 1;
	else
	{
		var.newstr = apend_char_str(var.newstr, str[*i]);
		*i += 1;
	}
	return (var.newstr);
}
char	*ft_expending_word(char *str,t_env *envp)
{
	int		i;
	t_var	var;

	i = 0;
	var.sinqot = 1;
	var.dobqot = 1;
	var.newstr = NULL;

	while (str[i])
	{
		var.var = NULL;
		if (str[i] == '\'' && var.dobqot == 1)
			var.sinqot *= (-1);
		else if (str[i] == '\"' && var.sinqot == 1)
			var.dobqot *= (-1);
		if (str[i] == '$' && str[i + 1] == '\0')
			var.newstr = apend_char_str(var.newstr, str[i++]);
		else if (str[i] == '$' && var.sinqot == 1 && ft_isalpha(str[i + 1]))
		{
			while (str[++i] && ft_isalnum(str[i]))
				var.var = apend_char_str(var.var, str[i]);
		}
		else if (str[i] == '$' && ft_isdigit(str[i + 1]))
			i += 2;
		else if (str[i] != '\0')
			var.newstr = add_to_str(str, var, &i);
		if (var.var != NULL)
			var.newstr = expend_it(var.var, var.newstr,envp);
	}
	free (str);
	return (var.newstr);
}

char	*remove_qout(char *str)
{
	int		i;
	int		sinqot;
	int		dobqot;
	char	*newstr;

	i = 0;
	sinqot = 1;
	dobqot = 1;
	newstr = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && dobqot == 1)
			sinqot *= (-1);
		if (str[i] == '\"' && sinqot == 1)
			dobqot *= (-1);
		if (str[i] == '\'' && dobqot == 1)
			i++;
		else if (str[i] == '\"' && sinqot == 1)
			i++;
		else
		{
			newstr = apend_char_str(newstr, str[i]);
			i++;
		}
	}
	free(str);
	if (newstr == NULL)
		newstr = apend_char_str(newstr,'\0');
	return (newstr);
}

char	*ft_expending(t_lexer *lexer, char *str, t_token *token,t_env *envp)
{
	char *newstr;
	if (!lexer)
		newstr = ft_expending_word(str,envp);
	else
	{
		while (lexer->next != NULL)
			lexer = lexer->next;
		if (lexer->token != herduc)
			newstr = ft_expending_word(str,envp);
		else
			newstr = str;
		if (lexer->token != word && lexer->token != herduc && !newstr)
		{
			*token = error;
			newstr = str;
		}
	}
	 newstr = remove_qout(newstr);
	return (newstr);
}