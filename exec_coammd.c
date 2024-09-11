/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_coammd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:43:46 by omar              #+#    #+#             */
/*   Updated: 2024/09/03 10:16:26 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_data *data, t_var_us var, t_env *envp, char **env)
{
	if (execve(var.pth, data->cmd, env) == -1)
	{
		free_data(data);
		free_envp(envp);
		ft_free1(var.path);
		free_var(&var);
		exit(1);
	}
}

void	first_child(t_data *data, t_var_us var, char **env, t_env **envp)
{
	var.envp = *envp;
	check_file1(data, &var);
	check_cmd_build(data, envp, var);
	var.pth = ft_getenv(*envp, "PATH");
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
	else
		dup2(var.pipe[var.i][1], 1);
	close(var.pipe[var.i][0]);
	close(var.pipe[var.i][1]);
	ft_execve(data, var, *envp, env);
}

void	secund_command(t_data *data, t_var_us var, char **env, t_env **envp)
{
	var.envp = *envp;
	check_file1(data, &var);
	check_cmd_build(data, envp, var);
	var.pth = ft_getenv(*envp, "PATH");
	var.path = ft_split(var.pth, ':');
	var.pth = check_path(var, data);
	if (var.infd != -2)
	{
		dup2(var.infd, 0);
		close(var.infd);
	}
	else
		dup2(var.pipe[var.i - 1][0], 0);
	if (var.outfd != -2)
	{
		dup2(var.outfd, 1);
		close(var.outfd);
	}
	else
		dup2(var.pipe[var.i][1], 1);
	close(var.pipe[var.i - 1][0]);
	close(var.pipe[var.i][0]);
	close(var.pipe[var.i][1]);
	ft_execve(data, var, *envp, env);
}

void	last_command(t_data *data, t_var_us var, char **env, t_env **envp)
{
	var.envp = *envp;
	check_file1(data, &var);
	check_cmd_build(data, envp, var);
	var.pth = ft_getenv(*envp, "PATH");
	var.path = ft_split(var.pth, ':');
	var.pth = check_path(var, data);
	if (var.infd != -2)
	{
		dup2(var.infd, 0);
		close(var.infd);
	}
	else
		dup2(var.pipe[var.i - 1][0], 0);
	if (var.outfd != -2)
	{
		dup2(var.outfd, 1);
		close(var.outfd);
	}
	close(var.pipe[var.i - 1][0]);
	ft_execve(data, var, *envp, env);
}

void	handle_child(t_data *data, t_var_us var, char **env, t_env **envp)
{
	signal(SIGINT, child_handler);
	signal(SIGQUIT, child_handler1);
	if (var.i == 0)
		first_child(data, var, env, envp);
	if (var.i < var.cont_cmd - 1)
		secund_command(data, var, env, envp);
	else
		last_command(data, var, env, envp);
}
