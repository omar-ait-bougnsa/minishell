/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:43:51 by omar              #+#    #+#             */
/*   Updated: 2024/09/01 11:54:54 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data, t_env *env)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (data->cmd[1] && data->cmd[1][0] == '-')
	{
		printf("minshell: pwd: %s: invalid option\n", data->cmd[1]);
		return (1);
	}
	if (path == NULL)
	{
		printf("%s\n", env->pwd);
		return (0);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == (unsigned char)c)
			return (1);
		i++;
	}
	return (0);
}

int	execute_build1(t_data *data, t_env **envp)
{
	if (ft_strcmp(data->cmd[0], "env") == 0)
	{
		(*envp)->exit_status = ft_env(data, *envp);
		return (1);
	}
	if (ft_strcmp(data->cmd[0], "exit") == 0)
		ft_exit(data, *envp);
	if (ft_strcmp(data->cmd[0], "unset") == 0)
	{
		(*envp)->exit_status = ft_unset(data, envp);
		return (1);
	}
	return (0);
}

int	execut_buildin(t_data *data, t_env **envp)
{
	if (ft_strcmp(data->cmd[0], "echo") == 0)
	{
		(*envp)->exit_status = ft_echo(data);
		return (1);
	}
	if (ft_strcmp(data->cmd[0], "cd") == 0)
	{
		(*envp)->exit_status = ft_cd(data, *envp);
		return (1);
	}
	if (ft_strcmp(data->cmd[0], "pwd") == 0)
	{
		(*envp)->exit_status = ft_pwd(data, *envp);
		return (1);
	}
	if (ft_strcmp(data->cmd[0], "export") == 0)
	{
		(*envp)->exit_status = ft_export(data, envp);
		return (1);
	}
	if (execute_build1(data, envp))
		return (1);
	return (0);
}
