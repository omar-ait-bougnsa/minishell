#include "minishell.h"

void free_lexer(t_lexer *lexer) 
{
    t_lexer *next = lexer;
    if (!lexer)
		return;
    while (next!= NULL) 
	{
        lexer = next->next;
		free (next->data);
        free(next);
        next = lexer;
    }
}
char	*ft_strncpy(char *dest, char *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strsrch(char *str, char c)
{
	int	i;

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
char	*apend_char_str(char *str, char c)
{
	int		i;
	char	*new;

	i = 0;
	if (str == NULL)
	{
		if (!(new = malloc(2)))
			return (NULL);
		new[0] = c;
		new[1] = '\0';
		return (new);
	}
	i = ft_strlen(str);
	if (!(new = malloc(i + 2)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	free(str);
	return (new);
}
