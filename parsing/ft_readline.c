#include "minishell.h"

char *ft_readline(char *str)
{
    char *buf;
    int b;
    char *tr;
    write(1,str,ft_strlen(str));
    str = NULL;
    buf = ft_calloc (sizeof(char),10);
    b = 1;
    while (b > 0)
    {
        if (ft_strsrch(buf,'\n'))
             break;
        b = read(0,buf,10);
        buf[b] = '\0';
        tr = ft_strjoinn (str,buf);
        if(str)
            free (str);
        str = tr;
    }
    free (buf);
    return (str);
}