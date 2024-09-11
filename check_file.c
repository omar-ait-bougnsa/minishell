/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:43:42 by omar              #+#    #+#             */
/*   Updated: 2024/09/05 10:44:34 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input_files(t_file *new, t_var_us *var)
{
	if (new->infile == 1)
	{
		if (var->infd != -2)
			close(var->infd);
		var->infd = open(new->file, O_RDONLY);
	}
	else if (new->herdoc == 1)
	{
		if (var->infd != -2)
			close(var->infd);
		var->infd = new->fd[0];
	}
	if (var->infd == -1)
		return (1);
	return (0);
}

int	handle_output_files(t_file *new, t_var_us *var)
{
	if (new->outfile == 1)
	{
		if (var->outfd != -2)
			close(var->outfd);
		var->outfd = open(new->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	}
	else if (new->apend == 1)
	{
		if (var->outfd != -2)
			close(var->outfd);
		var->outfd = open(new->file, O_WRONLY | O_APPEND | O_CREAT, 0664);
	}
	if (var->outfd == -1)
		return (1);
	return (0);
}

int	handle_ambiguous_redirect(t_file *new)
{
	if (new->ambiguous == 1)
	{
		printf("minishell :%s: ambiguous redirect\n", new->file);
		return (1);
	}
	return (0);
}

int	check_file(t_data *data, t_var_us *var)
{
	t_file	*new;

	new = data->file;
	var->infd = -2;
	var->outfd = -2;
	while (new)
	{
		if (handle_input_files(new, var) || handle_output_files(new, var))
		{
			perror(new->file);
			return (1);
		}
		if (handle_ambiguous_redirect(new))
		{
			return (1);
		}
		new = new->next;
	}
	return (0);
}

void	check_file1(t_data *data, t_var_us *var)
{
	if (check_file(data, var) == 1)
	{
		free_data(data);
		free_envp(var->envp);
		free_var(var);
		rl_clear_history();
		exit(1);
	}
}
