/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:44:53 by omar              #+#    #+#             */
/*   Updated: 2024/09/03 10:21:35 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free1(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_file(t_file *file)
{
	t_file	*tmp;

	while (file)
	{
		tmp = file->next;
		free(file->file);
		free(file);
		file = tmp;
	}
}

void	free_envp(t_env *envp)
{
	t_env	*tmp;

	ft_free1(envp->env);
	while (envp)
	{
		tmp = envp;
		envp = envp->next;
		free(tmp->var);
		if (tmp->value)
			free(tmp->value);
		if (tmp->pwd)
			free(tmp->pwd);
		free(tmp);
	}
}

void	free_data(t_data *data)
{
	t_data	*tmp;

	while (data)
	{
		tmp = data->next;
		ft_free1(data->cmd);
		free_file(data->file);
		free(data);
		data = tmp;
	}
	free(data);
}

void	free_var(t_var_us *var)
{
	int	i;

	i = 0;
	if (!var)
		return ;
	if (var->pipe)
	{
		while (var->pipe[i])
		{
			free(var->pipe[i]);
			i++;
		}
		free(var->pipe);
	}
	if (var->id)
		free(var->id);
}
