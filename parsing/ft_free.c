#include "minishell.h"

void ft_free1(char **str)
{
	int i;

    if (str == NULL)
        return;
    i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free (str);
}

void free_file(t_file *file)
{
    t_file *tmp;
    while (file)
    {
        tmp = file->next;
        free (file->file);
        free (file);
        file = tmp;
    }
}

void free_envp(t_env *envp)
{
	t_env *tmp;

	while (envp)
	{
		tmp = envp;
		envp = envp->next;
		free(tmp->var);
        if (tmp->value)
		    free(tmp->value);
		free(tmp);
	}
}
void free_data (t_data *data)
{
    t_data *tmp;

    while (data)
    {
        tmp = data->next;
        ft_free1 (data->cmd);
        free_file(data->file);
        free(data);
        data = tmp;
    }
    free(data);
}
void free_exit(t_data *data,t_env *env)
{
    free(env);
    free_data(data);
}