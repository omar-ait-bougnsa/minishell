#include "minishell.h"

int count_listenv(t_env *env)
{
    int i;

    i = 0;
    while (env)
    {
        i++;
        env = env->next;
    }
    return (i);
}

void  sort_print1(t_env *env)
{
    int n;
    t_env *tmp;
    char *str;
    t_env *s1;

    str = ft_strdup("");
    n = count_listenv(env);
    while (n > 0)
    {
       tmp = env;
       s1 = tmp;
        while(tmp)
        {
            if (ft_strcmp (s1->var,str) <= 0)
            {
                s1 = tmp;
            }
            else if (ft_strcmp(s1->var,tmp->var) > 0 && ft_strcmp (tmp->var,str) > 0)
                s1 = tmp;
            tmp = tmp->next;
        }
        free(str);
        str = ft_strdup(s1->var);
        if (!s1->egnor)
        {
        printf ("declare -x ");
        printf ("%s",str);
        if (s1->value)
             printf ("\"%s\"\n",s1->value);
        else
            printf ("\n");
        }
        n--;
    }
}

void ft_export (t_data *data,t_env **env)
{
    if (data->cmd[1] == NULL)
    {
        sort_print1(*env);
    }
    else
        ft_setenv (&data->cmd[1],env);
}