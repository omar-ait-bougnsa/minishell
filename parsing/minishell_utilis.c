#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	i;
	size_t	j;

	if (s1 == NULL && s2 == NULL)
		return (0);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	s = malloc(sizeof(char) * (i + j + 1));
	if (s == NULL)
		return (0);
	ft_memcpy(s, s1, i);
	ft_memcpy(s + i, s2, j);
	s[j + i] = '\0';
	return (s);
}
