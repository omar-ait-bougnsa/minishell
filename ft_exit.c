/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:44:40 by omar              #+#    #+#             */
/*   Updated: 2024/09/05 11:13:25 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_var_free	g_var_f;

int	ft_var(char *str, int i, int res, int sign)
{
	if (str[i] != '\0')
	{
		ft_printf("bash: exit: ", str, ":numeric argument required\n");
		return (2);
	}
	return ((res * sign));
}

int	check_long(int sign, long long res, char *str, int i)
{
	if (sign == 1 && res > (LLONG_MAX - (str[i] - '0')) / 10)
	{
		ft_printf("minshell: exit: ", str, ": numeric argument required\n");
		return (1);
	}
	else if (sign == -1 && (-res) < (LLONG_MIN + (str[i] - '0')) / 10)
	{
		ft_printf("minshell: exit:", str, ": numeric argument required\n");
		return (1);
	}
	return (0);
}

int	ft_atoi(char *str)
{
	long long	res;
	int			sign;
	int			i;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (check_long(sign, res, str, i))
			return (2);
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (ft_var(str, i, res, sign));
}

void	ft_exit(t_data *data, t_env *envp)
{
	int	exit_s;

	if (data->cmd[1] == NULL)
		exit_s = envp->exit_status;
	else if (data->cmd[2] != NULL)
	{
		ft_printf("minishell", ":exit: too ", "many arguments\n");
		return ;
	}
	else
		exit_s = ft_atoi(data->cmd[1]);
	if (g_var_f.flg != 1)
		printf("exit\n");
	free_data(data);
	free_envp(envp);
	free_var(g_var_f.var);
	exit(exit_s);
}
