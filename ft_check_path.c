/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:44:23 by omar              #+#    #+#             */
/*   Updated: 2024/09/03 10:00:51 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (dest == NULL && src == NULL)
		return (0);
	if (dest == src)
		return (dest);
	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (i < size)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

void	ft_free_exit(char *str, t_var_us var, int n, t_data *data)
{
	ft_free1(var.path);
	if (str != NULL)
		printf("%s", str);
	free_data(data);
	free_envp(var.envp);
	free_var(&var);
	rl_clear_history();
	exit(n);
}

int	ft_check_access(t_var_us *var, t_data *data)
{
	if (access(data->cmd[0], F_OK) != -1)
	{
		var->fd = open(data->cmd[0], O_CREAT);
		if (var->fd == -1)
		{
			perror(data->cmd[0]);
			ft_free_exit(NULL, *var, 126, data);
		}
		close(var->fd);
		if (access(data->cmd[0], X_OK) == -1)
		{
			printf("minshell: %s: Permission denied\n", data->cmd[0]);
			ft_free_exit(NULL, *var, 126, data);
		}
	}
	else
	{
		printf("minshell: %s: No such file or directory\n", data->cmd[0]);
		ft_free_exit(NULL, *var, 127, data);
	}
	return (1);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*s;
	size_t	i;
	size_t	j;

	if (s1 == NULL && s2 == NULL)
		return (0);
	if (!s1)
		return ((char *)s2);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	s = malloc(sizeof(char) * (i + j + 2));
	if (s == NULL)
		return (0);
	ft_memcpy(s, s1, i);
	s[i++] = '/';
	ft_memcpy(s + i, s2, j);
	s[j + i] = '\0';
	return (s);
}

char	*check_path(t_var_us var, t_data *data)
{
	int	i;

	i = 0;
	if (data->cmd[0][0] == '\0')
		ft_free_exit(" :command not found\n", var, 127, data);
	if (data->cmd[0][0] == '.' && data->cmd[0][1] == '\0')
		ft_free_exit(".: filename argument required\n", var, 2, data);
	if (ft_strsrch(data->cmd[0], '/') != 0 || var.path[0] == NULL)
	{
		if (ft_check_access(&var, data) == 1)
			return (data->cmd[0]);
	}
	while (var.path[i])
	{
		var.pth = ft_strjoin1(var.path[i++], data->cmd[0]);
		if (access(var.pth, X_OK) == 0)
			return (var.pth);
		free(var.pth);
	}
	if (var.path[i] == NULL)
	{
		printf("%s: command not found\n", data->cmd[0]);
		ft_free_exit(NULL, var, 127, data);
	}
	return (NULL);
}
