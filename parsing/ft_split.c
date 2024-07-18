#include "minishell.h"

int count_word (char *str,char c)
{
    int i;
    int count;
    if (str == NULL)
        return(0);
    count = 0;
    i = 0;
    while (str[i])
    {
        while (str[i] == c)
            i++;
        if (str[i] == '\0')
            break;
        count++;
        while (str[i] != '\0' && str[i] != c)
            i++;
    }
    return (count);
}
char *ft_substr (char *str,int start,int len)
{
    int i;
    char *s;

    i = 0;
    s = malloc (sizeof(char) * len + 1);
    if (s == NULL)
        return (NULL);
    while (i< len)
    {
        s[i] = str[start];
        i++;
        start++;
    }
    s[i] = '\0';
    return (s);
}
char  **ft_split (char *str,char c)
{
    int i;
    int j;
    int n;
    char **s;

    i = 0;
    j = 0;
    n = count_word (str,c);
    s = malloc (sizeof (char *) * n + 1);
    if (s == NULL)
        return (NULL);
    while (str && str[i])
    {
        while (str[i] == c)
            i++;
        n = i;
        if (str[i] == '\0')
            break;
        while (str[i] != '\0' && str[i] != c)
            i++;
        s[j] = ft_substr (str,n,i - n);
        j++;
    }
    s[j] = NULL;
    return (s);
}