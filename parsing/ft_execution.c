#include "minishell.h"

void check_file(t_data *data, t_var_us *var)
{
	var->infd = -2;
	var->outfd = -2;
	while (data->file)
	{
		if (data->file->infile == 1)
			var->infd = open(data->file->file, O_RDONLY);
		else if (data->file->outfile == 1)
			var->outfd = open(data->file->file, O_RDWR);
		if (var->infd == -1 || var->outfd == -1)
		{
			perror(data->file->file);
			exit(126);
		}
		data->file = data->file->next;
	}
}

int count_list(t_data *data)
{
	int cont;

	cont = 0;
	while (data)
	{
		cont++;
		data = data->next;
	}
	return (cont);
}

void simple_execut(t_data *data, t_var_us var, char **env)
{
	var.path = ft_split(var.pth, ':');
	var.pth = check_path(var, data->cmd);
	if (var.pth)
		check_file(data, &var);
	if (var.infd != -2)
	{
		dup2(var.infd, 0);
		close(var.infd);
	}
	if (var.outfd != -2)
		dup2(var.outfd, 1);
	execve(var.pth, data->cmd, env);
}
int ft_strcmp(char *s1,char *s2)
{
    int i;
    i = 0;
     while (s1[i] && s2[i] && s1[i] == s2[i])
         i++;
    return(s1[i] - s2[i]);
}
int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *p1;
	unsigned char *p2;
	size_t i;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = 0;
	while (n--)
	{
		if (p1[i] != p2[i] || p1[i] == 0 || p2[i] == 0)
		{
			return (p1[i] - p2[i]);
		}
		i++;
	}
	return (0);
}
char *ft_strjoinn(char *s1, char *ss2)
{
	int i;
	int j;
	char *result;

	if (!s1 && !ss2)
		return (NULL);
	if (!s1)
		return ((char *)ss2);
	if (!ss2)
		return ((char *)s1);
	i = ft_strlen(s1);
	j = ft_strlen(ss2);
	result = ((char *)malloc(i + j + 1));
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, i);
	ft_memcpy(result + i, ss2, j);
	result[i + j] = '\0';
	return (result);
}
void change_env(t_data *data, t_env *env)
{

	t_env *current = env;
	while (current)
	{
		if (ft_strncmp(current->var, "OLDPWD", 6) == 0)
		{
			free(current->value);
			current->value = ft_strdup(data->oldpwd);
		}
		if (ft_strncmp(current->var, "PWD", 3) == 0)
		{
			free(current->value);
			current->value = ft_strdup(data->newpwd);
		}
		current = current->next;
	}
}
void ft_cd(t_data *data, t_env *env)
{
	char *home = getenv("HOME");
	char *tmp = getcwd(NULL, 0);

	if (tmp == NULL)
	{
		perror("getcwd");
		return;
	}
	if (data->cmd[1] == NULL)
	{
		if (home != NULL)
		{
			if (chdir(home) == 0)
			{
				data->newpwd = ft_strdup(home);
				data->oldpwd = tmp;
				change_env(data, env);
			}
			else
			{
				write(2, "bash: ", 7);

				perror(home);
			}
		}
		else
			write(2, "bash: cd: HOME not set\n", 23);
		free(tmp);
		return;
	}
	if (data->cmd[2] != NULL)
	{
		write(2, "bash: cd: too many arguments\n", 29);
		free(tmp);
		return;
	}
	if (chdir(data->cmd[1]) != 0)
	{
		write(2, "ba1sh: cd: ", 10);
		perror(data->cmd[1]);
	}
	else
	{
		data->newpwd = getcwd(NULL, 0);
		data->oldpwd = tmp;
		change_env(data, env);
	}
	free(tmp);
}
int check_newline_flag(t_data *data, int *i)
{
	int j;

	while (data->cmd[*i] && data->cmd[*i][0] == '-' && data->cmd[*i][1] == 'n')
	{
		j = 1;
		while (data->cmd[*i][j] == 'n')
			j++;
		if (data->cmd[*i][j] == '\0')
		{
			(*i)++;
			return (0);
		}
		else
			break;
	}
	return (1);
}

void ft_echo(t_data *data)
{
	int i;
	int newline;

	i = 1;
	newline = check_newline_flag(data, &i);
	while (data->cmd[i])
	{
		printf("%s", data->cmd[i]);
		if (data->cmd[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

void ft_pwd(t_data *data)
{
	char *path = getcwd(NULL, 0);
	if (data->cmd[1] != NULL)
		if (data->cmd[1][0] == '-')
		{
			printf("bash: pwd: %s: invalid option\npwd: usage: pwd [-LP]\n", data->cmd[1]);
			return;
		}
	if (path == NULL)
	{
		perror("bash: ");
		return;
	}
	printf("%s\n", path);
	free(path);
}
void free_env(t_env *env)
{
	t_env *temp;

	while (env != NULL)
	{
		temp = env->next;
		free(env);
		env = temp;
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
		free(tmp->value);
		free(tmp);
	}
}

int ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
    long long res;
    int sign;
    int i;

    i = 0;
    res = 0;
    sign = 1;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-')
        sign *= -1;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            if (res > (LLONG_MAX - (str[i] - '0')) / 10)
            {
                printf("exit\n");
                printf("bash: exit: %s: numeric argument required\n", str);
                exit(1);
            }
            res = res * 10 + str[i] - '0';
        }
        else
        {
            printf("exit\n");
            printf("bash: exit: %s: numeric argument required\n", str);
            exit(1);
        }
        i++;
    }
    return (res * sign);
}
void ft_exit(t_data *data)
{
	int n;
	if(data->cmd[1]==NULL)
	{
		printf("exit\n");
		exit(0);
	}
	else 
		{
			n=ft_atoi(data->cmd[1]);
			printf("exit\n");
			exit(n);
		}

}
void ft_env(t_data *data, t_env *evnp)
{
	if (data->cmd[1] == NULL)
	{
		while (evnp)
		{
			if (ft_strchr(evnp->var,'=') && evnp->egnor != 1)
			{
				printf("%s", evnp->var);
				printf("%s\n", evnp->value);
			}
			evnp = evnp->next;
		}
	}
}
int check_buildin(t_data *data, t_env **envp)
{
	if (ft_strcmp(data->cmd[0], "echo") == 0)
	{
		ft_echo(data);
		return (1);
	}
	if (ft_strcmp(data->cmd[0], "cd") == 0)
	{
		ft_cd(data, *envp);
		return (1);
	}
	if (ft_strcmp(data->cmd[0], "pwd") == 0)
	{
		ft_pwd(data);
		return (1);
	}
	if (ft_strcmp(data->cmd[0], "export") == 0)
	{
		ft_export(data,envp);
		return (1);
	}
	if (ft_strcmp(data->cmd[0], "env") == 0)
	{
		ft_env(data, *envp);
		return (1);
	}
	if (ft_strcmp(data->cmd[0], "exit") == 0)
	{
		ft_exit(data);
		return (1);
	}
	return (0);
}
void simple_cmd(t_data *data, char **env, t_env **envp)
{
	int id;
	t_var_us var;

	if (check_buildin(data, envp))
		return;
	var.pth = ft_getenv(*envp,"PATH");
	id = fork();
	if (id < 0)
		return;
	if (id == 0)
		simple_execut(data, var, env);
	else
		waitpid(id, 0, 0);
}

void ft_execution(t_data *data, char **env, t_env **envp)
{
	int cont;

	if (data)
	{
		cont = count_list(data);
		if (cont == 1)
			simple_cmd(data, env, envp);
		else
			execut_comand(data, env);
	}
}