#include "minishell.h"


char *ft_getenv (t_env *env,char *str)
{
    int i;

    if (!str)
        return (NULL);
    while (env)
    {
        i = 0;
        while (str[i] && str[i] == env->var[i])
            i++;
        if (str[i] == '\0' && env->var[i] == '=')
            return (env->value);
        env = env->next;
    }
    return (NULL);
}