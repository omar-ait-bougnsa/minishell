/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:43:36 by omar              #+#    #+#             */
/*   Updated: 2024/09/03 10:20:57 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit(t_data *data, t_var_us var, t_env *envp, int exit_s)
{
	free_data(data);
	free_envp(envp);
	free_var(&var);
	rl_clear_history();
	exit(exit_s);
}

int	is_builtin_command(char *cmd)
{
	if (!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"env"))
		return (0);
	if (!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "echo"))
		return (0);
	if (!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset"))
		return (0);
	return (1);
}

int	check_cmd_build(t_data *data, t_env **envp, t_var_us var)
{
	int	flag;
	int	exit_s;

	flag = 0;
	if (!data->cmd || !data->cmd[0])
		free_and_exit(data, var, *envp, 0);
	if (!is_builtin_command(data->cmd[0]))
		flag = 1;
	if (flag == 1)
	{
		if (var.outfd != -2)
			dup2(var.outfd, 1);
		else if (var.i < var.cont_cmd - 1)
		{
			dup2(var.pipe[var.i][1], 1);
			close(var.pipe[var.i][0]);
			close(var.pipe[var.i][1]);
		}
		if (var.i > 0)
			close(var.pipe[var.i - 1][0]);
		execut_buildin(data, envp);
		exit_s = (*envp)->exit_status;
		free_and_exit(data, var, *envp, exit_s);
	}
	return (0);
}

void	dup_and_execut(t_data *data, t_var_us var, t_env **envp, int flag)
{
	var.fd = dup(1);
	if (var.outfd != -2)
	{
		dup2(var.outfd, 1);
		close(var.outfd);
	}
	if (var.infd != -2)
		close(var.infd);
	if (flag == 1)
		execut_buildin(data, envp);
	dup2(var.fd, 1);
	close(var.fd);
}

int	check_singcmd_build(t_data *data, t_env **envp)
{
	int			flag;
	t_var_us	var;

	flag = 0;
	if (!data->cmd || !data->cmd[0])
		flag = 2;
	else if (!is_builtin_command(data->cmd[0]))
		flag = 1;
	if (flag != 0)
	{
		if (check_file(data, &var))
		{
			(*envp)->exit_status = 1;
			return (1);
		}
		dup_and_execut(data, var, envp, flag);
		return (1);
	}
	return (0);
}
