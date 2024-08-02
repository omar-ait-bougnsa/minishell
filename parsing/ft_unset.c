#include "minishell.h"

void ft_unset(t_data *data,t_env **envp)
{
    t_env *new;
    t_env *tmp;
    int i;
    i  = 1;
    while (data->cmd[i])
    {
        new = *envp;
        tmp = *envp;
        while (new)
        {
            if (!strncmp(data->cmd[i],new->var,ft_strlen(data->cmd[i])))
            {
                free(new->var);
                if(new->value)
                     free (new->value);
                tmp->next = new->next;
                free(new);
                break;
            }
            tmp = new;
            new = new->next;
        }
    i++;
    }
}