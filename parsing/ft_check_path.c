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
// void	print_error(char *p, t_var_us *var, char **cmd)
// {
// 	perror(p);
// 	//ft_free1(var->path);
// 	exit(126);
// }

void	ft_free_exit(char *str, t_var_us *var, int n, char **cmd)
{
	printf("%s\n",str);
	str = NULL;
	if (cmd[0] == NULL)
		free(cmd);
	exit(n);
}

int	ft_check_access(t_var_us *var, char **cmd)
{
	if (access(cmd[0], F_OK) != -1)
	{
		var->fd = open(cmd[0], O_CREAT);
		if (access(cmd[0], X_OK) == -1 || var->fd == -1)
		{
			perror(cmd[0]);
			//ft_free1(var->path);
			//ft_free1(cmd);
			if (var->fd != -1)
				close(var->fd);
			exit(126);
		}
		close(var->fd);
	}
	else
	{
		perror(cmd[0]);
		//ft_free1(var->path);
		//ft_free1(cmd);
		exit(127);
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
char	*check_path(t_var_us *var, char **cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == NULL)
		ft_free_exit(": : command not found\n", var, 127, cmd);
	if (cmd[0][0] == '.' && cmd[0][1] == '\0')
		ft_free_exit(".: filename argument required\n", var, 2, cmd);
	if (ft_strsrch(cmd[0], '/') != 0 || var->path[0] == NULL)
	{
		if (ft_check_access(var, cmd) == 1)
			return (cmd[0]);
	}
	while (var->path[i])
	{
		var->pth = ft_strjoin1(var->path[i++], cmd[0]);
		if (access(var->pth, X_OK) == 0)
			return (var->pth);
		free(var->pth);
	}
	if (var->path[i] == NULL)
	{
		///ft_putstr(cmd[0]);
		ft_free_exit(" : command not found\n", var, 127, cmd);
	}
	return (NULL);
}