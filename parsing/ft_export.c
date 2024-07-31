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

void  sort_print(t_env *env)
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
int	ft_isalnumm(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)|| c=='=')
		return (1);
	return (0);
}

int ft_isalnumms(char *str)
{
    int i;
    i=0;
    while (str[i])
    {
<<<<<<< HEAD
        sort_print(*env);
=======
        if(ft_isalnumm(str[i])==0)
            return(0);
        i++;
>>>>>>> af190a4 (a)
    }
    return(1);
}
void ft_export(t_data *data, t_env **env)
{
    int i = 1;

    if (data->cmd[1] == NULL)
        sort_print1(*env);
    else if (data->cmd[1][0] == '\0')
        printf("export: `': not a valid identifier\n");
    else
    {
        while (data->cmd[i])
        {
            if (data->cmd[i][0] == '-' && data->cmd[i][1] == '-')
                printf("minishell: export: --: invalid option\n");
            else if (data->cmd[i][0] == '-')
                printf("minishell: export: -%c: invalid option\n", data->cmd[i][1]);
            else if (ft_isalpha(data->cmd[i][0]) == 0)
                printf("minishell: export:` %s': not a valid identifier\n", data->cmd[i]);
            else if (ft_isalnumms(data->cmd[i]) == 0)
                printf("minishell: export:` %s': not a valid identifier\n", data->cmd[i]);
            else
                ft_setenv(data->cmd[i], env);
            i++;
        }
    }
}