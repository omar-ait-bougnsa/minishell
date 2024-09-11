/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:44:31 by omar              #+#    #+#             */
/*   Updated: 2024/08/26 12:44:32 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print(t_env *envp)
{
	while (envp)
	{
		if (envp->value && envp->egnor != 1)
		{
			printf("%s", envp->var);
			printf("%s\n", envp->value);
		}
		envp = envp->next;
	}
}

int	ft_env(t_data *data, t_env *evnp)
{
	if (data->cmd[1] == NULL)
		print(evnp);
	else if (data->cmd[1][0] == '-')
	{
		ft_printf("env: invalid option -- '", data->cmd[1], "\n");
		return (125);
	}
	else
	{
		ft_printf("env: ‘", data->cmd[1], "’: No such file or directory\n");
		return (127);
	}
	return (0);
}
