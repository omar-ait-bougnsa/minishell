#include "minishell.h"

void	check_file(t_data *data, t_var_us *var)
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

int	count_list(t_data *data)
{
	int	cont;

	cont = 0;
	while (data)
	{
		cont++;
		data = data->next;
	}
	return (cont);
}

void	simple_execut(t_data *data, t_var_us var, char **env)
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
void	simple_cmd(t_data *data, char **env)
{
	int			id;
	t_var_us	var;

	var.pth = getenv("PATH");
	id = fork();
	if (id < 0)
		return ;
	if (id == 0)
		simple_execut(data, var, env);
	else
		waitpid(id, 0, 0);
}

void	ft_execution(t_data *data, char **env)
{
	int cont;

	if (data)
	{
		cont = count_list(data);
		if (cont == 1)
			simple_cmd(data, env);
		else
			execut_comand(data,env);
	}
}