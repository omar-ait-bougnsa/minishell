
#include "minishell.h"

int	ft_outredire(t_lexer **lexer, char *len,t_env *envp)
{
	int		i;
	char	*str;

	i = 0;
	while (len[i] == '>')
		i++;
	str = malloc(i + 1);
	if (str == NULL)
		return (0);
	ft_strncpy(str, len, i);
	apend_in_struct(lexer, str, outredire,envp);
	return (i);
}

int	ft_inredire(t_lexer **lexer, char *len,t_env *envp)
{
	int		i;
	char	*str;

	i = 0;
	while (len[i] == '<')
		i++;
	str = malloc(i + 1);
	if (str == NULL)
		return (0);
	ft_strncpy(str, len, i);
	apend_in_struct(lexer, str, inredire,envp);
	return (i);
}

int	ft_pipe(t_lexer **lexer, char *len,t_env *envp)
{
	int		i;
	char	*str;

	i = 0;
	while (len[i] == '|')
		i++;
	str = malloc(i + 1);
	if (str == NULL)
		return (0);
	ft_strncpy(str, len, i);
	apend_in_struct(lexer, str, pipe1,envp);
	return (i);
}
int	ft_word(t_lexer **lexer, char *len,t_env *envp)
{
	int		singl;
	int		doubl;
	int		i;
	char	*str;

	i = 0;
	singl = 1;
	doubl = 1;
	while (len[i] && ft_token(len, i, &singl, &doubl))
		i++;
	if (len[i] == '\'' || len[i] == '\"')
		i++;
	str = malloc(i + 1);
	if (str == NULL)
		return (0);
	str = ft_strncpy(str, len, i);
	apend_in_struct(lexer, str, word,envp);
	return (i);
}
int	ft_word_in_qout(t_lexer **lexer, char *len,t_env *envp)
{
	int		i;
	char	*str;

	i = 0;
	i = get_next_qout(&len[i]);
	str = malloc(i + 1);
	if (str == NULL)
		return (0);
	ft_strncpy(str, len, i);
	apend_in_struct(lexer, str, word,envp);
	return (i);
}
void	lexer_phase(char *len, t_lexer **lexer,t_env *envp)
{
	int		i;

	i = 0;
	*lexer = NULL;
	while (len[i])
	{
		if (len[i] == '\"' || len[i] == '\'')
			i += ft_word_in_qout(lexer, &len[i],envp);
		else if (len[i] == '>')
			i += ft_outredire(lexer, &len[i],envp);
		else if (len[i] == '<')
			i += ft_inredire(lexer, &len[i],envp);
		else if (len[i] == '|')
			i += ft_pipe(lexer, &len[i],envp);
		else if (len[i] == ' ' || len[i] == '\t')
			i++;
		else
			i += ft_word(lexer, &len[i],envp);
	}
	syntax_error(lexer);
}
