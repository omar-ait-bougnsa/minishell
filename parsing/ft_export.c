#include "minishell.h"

int	ft_isalnumm(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)|| c=='=')
		return (1);
	return (0);
}
int ft_check_str(char *str)
{
    int i;
    i = 0;
    while (str[i])
    {
        if (!ft_isalnumm (str[i]))
            return(0);
        i++;
    }
    return (1);
}
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
int ft_strscmp (char *s1,char *s2,char c)
{
    int i;
    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i] && s1[i +1] != c && s2[i +1] != c)
        i++;
    return (s1[i] - s2[i]);
}
int set_to_env(char *env,t_env **envp)
{
    t_env *new;
    new = *envp;
    while (new)
    {
        if (!ft_strscmp(new->var,env,'+'))
        {
           env = ft_strsrch (env,'=');
            env = ft_strjoinn (new->value,&env[1]);
            free(new->value);
            new->value = env;
            return (1);
        }
        new = new->next;
    }
    return (0);
}
void ft_export (t_data *data,t_env **env)
{
    char *str;
    int i;
    i = 1;
    if (data->cmd[1] == NULL)
        sort_print(*env);
    else
    {
        while (data->cmd[i])
        {
        str = ft_strsrch(data->cmd[i],'+');
        if (str && str[1] == '=')
             set_to_env(data->cmd[i],env);
        else  if (data->cmd[i][0] == '-' && data->cmd[i][1] == '-')
                printf("minishell: export: --: invalid option\n");
        else if (data->cmd[i][0] == '-')
                printf("minishell: export: -%c: invalid option\n", data->cmd[i][1]);
        else if (ft_isalpha(data->cmd[i][0]) == 0)
                printf("minishell: export:` %s': not a valid identifier\n", data->cmd[i]);
        else if (ft_check_str(data->cmd[i]) == 0)
                printf("minishell: export:` %s': not a valid identifier\n", data->cmd[i]);
        else
          ft_setenv (data->cmd[i],env);
        i++;
        }
    }
}