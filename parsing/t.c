#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char *ft_getvar (char *str)
{
    int i;
    char *newstr;
    int n;

    i = 0;
    n = 0;
    while (str[n] && str[n] != '=' && str[n] != '+')
        n++;
    if (str[n] == '=' || str[n] == '+')
        n++;
    newstr = malloc(n+1);
    if (newstr == NULL)
        return(NULL);
    n = 0;
    while (str[i] && str[i] != '=')
    {
        if (str[i] != '+')
             newstr[n++] = str[i];
        i++;
    }
    if (str[i] == '=')
        newstr[n++] = '=';
    newstr[n] = '\0';
    return (newstr);
}

int main()
{
    char *str =ft_getvar ("hell+kk=");
    printf ("%s\n",str);
}