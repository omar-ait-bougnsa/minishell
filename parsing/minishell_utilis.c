#include "minishell.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*s;
// 	size_t	i;
// 	size_t	j;

// 	if (s1 == NULL && s2 == NULL)
// 		return (0);
// 	if (!s1)
// 		return ((char *)s2);
// 	if (!s2)
// 		return ((char *)s1);
// 	i = ft_strlen(s1);
// 	j = ft_strlen(s2);
// 	s = malloc(sizeof(char) * (i + j + 1));
// 	if (s == NULL)
// 		return (0);
// 	ft_memcpy(s, s1, i);
// 	ft_memcpy(s + i, s2, j);
// 	s[j + i] = '\0';
// 	return (s);
// }
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
