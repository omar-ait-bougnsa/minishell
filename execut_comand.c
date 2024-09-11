/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_comand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:43:56 by omar              #+#    #+#             */
/*   Updated: 2024/09/05 10:46:56 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_var_free	g_var_f;

void	init_vars(t_var_us *var, t_data *data)
{
	g_var_f.flg = 1;
	var->i = 0;
	var->cont_cmd = count_list(data);
	var->id = ft_calloc(sizeof(int), var->cont_cmd + 1);
	var->pipe = ft_calloc(sizeof(int *), var->cont_cmd + 1);
	if (var->id == NULL || !var->pipe)
		return ;
	g_var_f.var = var;
}

void	close_pipes(t_var_us var)
{
	if (var.i > 0)
		close(var.pipe[var.i - 1][0]);
	if (var.i < var.cont_cmd - 1)
		close(var.pipe[var.i][1]);
}

void	wait_for_children(t_var_us var, t_env *envp)
{
	int	status;

	var.i = 0;
	while (var.i < var.cont_cmd)
	{
		waitpid(var.id[var.i], &status, 0);
		var.i++;
		check_status(status, envp);
	}
	free_var(&var);
}

void	free_node(t_data *tmp)
{
	free_file(tmp->file);
	ft_free1(tmp->cmd);
	free(tmp);
}

void	execut_comand(t_data **data, char **env, t_env **envp)
{
	t_var_us	var;
	t_data		*tmp;

	init_vars(&var, *data);
	while (var.i < var.cont_cmd)
	{
		var.pipe[var.i] = malloc(sizeof(int *) * 2);
		if (var.i < var.cont_cmd - 1)
			var.n = pipe(var.pipe[var.i]);
		var.id[var.i] = fork();
		if (var.id[var.i] == -1 || var.n == -1)
		{
			perror(NULL);
			return ;
		}
		if (var.id[var.i] == 0)
			handle_child(*data, var, env, envp);
		close_pipes(var);
		var.i++;
		tmp = (*data)->next;
		free_node(*data);
		*data = tmp;
	}
	wait_for_children(var, *envp);
}
