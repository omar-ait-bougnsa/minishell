#include "minishell.h"

void	ft_lstadd_backenv(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!env || !new)
		return ;
	if (*env)
	{
		tmp = *env;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*env = new;
}

char *ft_getvar (char *str)
{
    int i;
    char *newstr;
    int n;

    i = 0;
    n = 0;
    while (str[n] && str[n] != '=')
        n++;
    if (str[n] == '=')
        n++;
    newstr = malloc(n+1);
    if (newstr == NULL)
        return(NULL);
    while (i < n)
    {
        newstr[i] = str[i];
        i++;
    }
    newstr[i] = '\0';
    return (newstr);
}
int  check_var (char *var,char *str,t_env *envp)
{
    int n;

    n = ft_strlen(var);

    while (envp)
    {
        if (!ft_strncmp(envp->var,var,n))
        {
        if (ft_strchr (var,'='))
        {
            if (envp->value)
                free(envp->value);
            envp->value = str;
            envp->egnor =0;
        }
            return(1);
        }
        envp = envp->next;
    }
    return (0);
}
void ft_setenv(char *env,t_env **envp)
{
    char *str;
    char *var;
    t_env *newenv;
   
        var = ft_getvar(env);
        str = ft_strsrch (env,'=');
        if (str)
            str = ft_strdup(&str[1]);
       if (check_var(var,str,*envp));
       else
       {
        newenv = ft_calloc (sizeof(t_env),1);
        if (!newenv)
            return;
        newenv->value = str;
        newenv->var = var;
        ft_lstadd_backenv(envp,newenv);
       }
}
