/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:45:02 by omar              #+#    #+#             */
/*   Updated: 2024/09/05 10:19:40 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_var_free	g_var_f;

void	free_herdoc(int exit_s, char *str)
{
	if (str)
		printf("%s\n", str);
	free_data(g_var_f.data);
	free_envp(g_var_f.env);
	clear_history();
	exit(exit_s);
}

int	cont_herd(t_data *data)
{
	t_file	*newfile;
	int		i;

	i = 0;
	while (data)
	{
		newfile = data->file;
		while (newfile)
		{
			if (newfile->herdoc == 1)
				i++;
			newfile = newfile->next;
		}
		data = data->next;
	}
	return (i);
}

void	open_herdoc(t_file *newfile, t_env *envp)
{
	char	*line;

	signal(SIGINT, f);
	while (1)
	{
		line = readline(">");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, newfile->file) == 0)
		{
			free(line);
			free_herdoc(0, NULL);
		}
		line = apend_char_str(line, '\n');
		if (!newfile->expand)
			line = expending_herd(line, envp);
		write(newfile->fd[1], line, ft_strlen(line));
		free(line);
	}
	if (line == NULL)
	{
		printf("here-document delimited by end-of-file(wanted`%s')\n",
			newfile->file);
		free_herdoc(0, NULL);
	}
}

int	wait_herdoc(int pid, t_file *newfile)
{
	int	status;

	waitpid(pid, &status, 0);
	if ((status >> 8) == 130)
	{
		write(1, "\n", 2);
		close(newfile->fd[1]);
		return (1);
	}
	close(newfile->fd[1]);
	return (0);
}

int	ft_herdoc(t_data *data, t_env *envp)
{
	t_file	*newfile;
	int		pid;

	if (cont_herd(data) > 16)
		free_herdoc(2, "maximum here-document count exceeded");
	while (data)
	{
		newfile = data->file;
		while (newfile)
		{
			if (newfile->herdoc == 1)
			{
				pipe(newfile->fd);
				pid = fork();
				if (pid == 0)
					open_herdoc(newfile, envp);
				if (wait_herdoc(pid, newfile))
					return (1);
			}
			newfile = newfile->next;
		}
		data = data->next;
	}
	return (0);
}
