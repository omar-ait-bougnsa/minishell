/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:44:36 by omar              #+#    #+#             */
/*   Updated: 2024/09/05 12:50:15 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_var_free	g_var_f;

void	simple_execut(t_data *data, char **env, t_env *envp)
{
	t_var_us	var;

	var.envp = envp;
	var.pipe = NULL;
	var.id = NULL;
	var.pth = ft_getenv(envp, "PATH");
	check_file1(data, &var);
	var.path = ft_split(var.pth, ':');
	var.pth = check_path(var, data);
	if (var.infd != -2)
	{
		dup2(var.infd, 0);
		close(var.infd);
	}
	if (var.outfd != -2)
	{
		dup2(var.outfd, 1);
		close(var.outfd);
	}
	ft_execve(data, var, envp, env);
}

void	ft_close(t_data *data)
{
	t_file	*newfile;

	while (data)
	{
		newfile = data->file;
		while (newfile)
		{
			if (newfile->herdoc == 1 && newfile->fd[0])
				close(newfile->fd[0]);
			newfile = newfile->next;
		}
		data = data->next;
	}
}

void	check_status(int status, t_env *envp)
{
	if (WIFSIGNALED(status))
	{
		envp->exit_status = 128 + WTERMSIG(status);
		if (envp->exit_status == 131)
			write(2, "Quit (core dumped\n", 19);
		else if (envp->exit_status == 130)
			write(1, "\n", 1);
	}
	else
		envp->exit_status = WEXITSTATUS(status);
}

void	simple_cmd(t_data *data, char **env, t_env **envp)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (check_singcmd_build(data, envp))
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		signal(SIGINT, child_handler);
		signal(SIGQUIT, child_handler1);
		simple_execut(data, env, *envp);
	}
	else
	{
		waitpid(pid, &status, 0);
		check_status(status, *envp);
	}
}

void	ft_execution(t_data **data, char **env, t_env **envp)
{
	int	cont;
	
	if (!*data)
		return;
	cont = count_list(*data);
	g_var_f.data = *data;
	g_var_f.env = *envp;
	g_var_f.var = NULL;
	g_var_f.flg = 0;
	signal(SIGINT, SIG_IGN);
	if (ft_herdoc(*data, *envp))
	{
		ft_close(*data);
		return ;
	}
	if (data)
	{
		if (cont == 1)
			simple_cmd(*data, env, envp);
		else
			execut_comand(data, env, envp);
		signal(SIGINT, handle_signal1);
		ft_close(*data);
	}
}
