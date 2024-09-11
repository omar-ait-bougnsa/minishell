/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar <omar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:44:27 by omar              #+#    #+#             */
/*   Updated: 2024/08/26 12:44:28 by omar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_newline_flag(t_data *data, int *i)
{
	int	j;
	int	found_flag;

	found_flag = 0;
	while (data->cmd[*i] && data->cmd[*i][0] == '-' && data->cmd[*i][1] == 'n')
	{
		j = 1;
		while (data->cmd[*i][j] == 'n')
			j++;
		if (data->cmd[*i][j] == '\0')
		{
			found_flag = 1;
			(*i)++;
		}
		else
			break ;
	}
	if (found_flag)
		return (0);
	else
		return (1);
}

int	ft_echo(t_data *data)
{
	int	i;
	int	newline;

	i = 1;
	newline = check_newline_flag(data, &i);
	while (data->cmd[i])
	{
		write(1, data->cmd[i], ft_strlen(data->cmd[i]));
		if (data->cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
