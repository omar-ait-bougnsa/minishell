/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:44:06 by omar              #+#    #+#             */
/*   Updated: 2024/09/02 16:52:50 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_no_argument(t_env *env, char *tmp)
{
	char	*newpwd;
	char	*oldpwd;
	char	*home;

	home = ft_getenv(env, "HOME");
	if (home != NULL)
	{
		if (chdir(home) != 0)
		{
			write(2, "minshell: cd: ", 10);
			perror(NULL);
			return ;
		}
		newpwd = ft_strjoinn("PWD=", home);
		oldpwd = ft_strjoinn("OLDPWD=", tmp);
		ft_setenv(oldpwd, &env);
		ft_setenv(newpwd, &env);
		free(newpwd);
		free(oldpwd);
		if (env->pwd)
			free(env->pwd);
		env->pwd = ft_strdup(home);
	}
	else
		write(2, "bash: cd: HOME not set\n", 23);
}

void change_and_free(char *oldpwd,char *newpwd,char *str,t_env *env)
{
		ft_setenv(oldpwd, &env);
		ft_setenv(newpwd, &env);
		free(newpwd);
		free(oldpwd);
		if (env->pwd)
			free (env->pwd);
		env->pwd = str;
}

int	handle_change_directory(t_data *data, t_env *env, char *tmp)
{
	char	*newpwd;
	char	*oldpwd;
	char	*str;

	if (data->cmd[1][0] == '\0')
		return (0);
	if (chdir(data->cmd[1]) != 0)
	{
		perror(data->cmd[1]);
		return (1);
	}
	else
	{
		str = getcwd(NULL, 0);
		if (!str)
		{
			perror("getcwd : ");
			return (0);
		}
		newpwd = ft_strjoinn("PWD=", str);
		oldpwd = ft_strjoinn("OLDPWD=", tmp);
		change_and_free(oldpwd,newpwd,str,env);
	}
	return (0);
}

int	ft_cd(t_data *data, t_env *env)
{
	char	*tmp;

	tmp = ft_getenv(env, "PWD");
	if (data->cmd[1] == NULL)
	{
		handle_no_argument(env, tmp);
		return (1);
	}
	if (data->cmd[2] != NULL)
	{
		write(2, "bash: cd: too many arguments\n", 29);
		return (1);
	}
	if (handle_change_directory(data, env, tmp))
		return (1);
	return (0);
}
