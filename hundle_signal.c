/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hundle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:01:18 by oait-bou          #+#    #+#             */
/*   Updated: 2024/09/03 14:56:40 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_var_free	g_var_f;

void	handle_signal1(int sig)
{
	(void)sig;
	printf("\n");
	g_var_f.exit_s = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	child_handler(int signum)
{
	(void)signum;
	exit(130);
}

void	child_handler1(int signum)
{
	(void)signum;
	exit(131);
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

void	f(int sig)
{
	(void)sig;
	free_data(g_var_f.data);
	free_envp(g_var_f.env);
	clear_history();
	exit(130);
}
