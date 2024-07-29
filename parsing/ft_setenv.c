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
void	ft_lstadd_backexpo(t_export **env, t_export *new)
{
	t_export	*tmp;

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
    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    newstr = malloc(i+2);
    if (newstr == NULL)
        return(NULL);
    i = 0;
    while (str[i] && str[i] != '=')
    {
        newstr[i] = str[i];
        i++;
    }
    newstr[i++] = '=';
    newstr[i] = '\0';
    return (newstr);
}

void ft_setenv(char **env,t_env **envp)
{
    char *str;
    char *var;
    t_env *newenv;
    int i;

    i = 0;
    while (env[i])
    {
        if(ft_strsrch (env[i],'='))
        {
        var = ft_getvar(env[i]);
        str = ft_strsrch (env[i],'=');
        str = ft_strdup(&str[1]);
        newenv = malloc (sizeof(t_env));
        if (!newenv)
            return;
        newenv->value = str;
        newenv->var = var;
        newenv->next = NULL;
        ft_lstadd_backenv(envp,newenv);
        }
        i++;
    
}
}
