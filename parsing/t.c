#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int ft_strlen(char *str)
{
    int i;
    i = 0;
    while (str[i])
        i++;
    return (i);
}
typedef struct s_env
{
    char *var;
    char *value;
    struct s_env *next;
}t_env;

char	*ft_strdup(char *str)
{
	int		i;
	char	*cp;

	i = 0;
	if (str == NULL)
		return (NULL);
	cp = malloc(ft_strlen(str) + 1);
	if (cp == NULL)
		return (NULL);
	while (str[i])
	{
		cp[i] = str[i];
		i++;
	}
	cp[i] = '\0';
	return (cp);
}
char	*ft_strsrch(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

void	ft_lstadd_back1(t_env **env, t_env *new)
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
t_env *ft_setenv(char **env,t_env *envp)
{
    char *str;
    char *var;
    t_env *newenv;
    int i;
    i = 0;
    envp = NULL;
    while (env[i])
    {
        var = ft_getvar(env[i]);
        str = ft_strsrch (env[i],'=');
        str = ft_strdup(&str[1]);
        //printf ("%s",env[i]);
        newenv = malloc (sizeof(t_env));
        if (!newenv)
            return(NULL);
        newenv->value = str;
        newenv->var = var;
        newenv->next = NULL;
        ft_lstadd_back1(&envp,newenv);
        i++;
    }
    return (envp);
}
int	ft_strcmp(char *s1,char *s2)
{

	size_t			i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
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
        if (str[i] == '\0')
            return (env->value);
        env = env->next;
    }
    return (NULL);
}
int main(int ac,char **av,char **env)
{
    t_env *senv;
    int i;
   senv =  ft_setenv(env,senv);
//    while(senv)
//    {
//     printf ("%s",senv->var);
//     printf ("%s\n",senv->value);
//     printf ("-------------\n");
//     senv = senv->next;
//    }
  char  *path = ft_getenv(senv,"USER");
 printf ("%s\n",path);

}
