/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:45:45 by omar              #+#    #+#             */
/*   Updated: 2024/09/05 11:14:14 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var_free	g_var_f;

int	check_quote(char *str)
{
	int	i;
	int	sinqot;
	int	dbqot;

	i = 0;
	sinqot = 1;
	dbqot = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && sinqot == 1)
			dbqot *= (-1);
		if (str[i] == '\'' && dbqot == 1)
			sinqot *= (-1);
		i++;
	}
	if (dbqot == -1 || sinqot == -1)
		return (0);
	return (1);
}

int	ft_token(char c, int *singl, int *doubl)
{
	if (c == '\'' && *doubl != -1)
		*singl *= -1;
	if (c == '\"' && *singl != -1)
		*doubl *= -1;
	if (ft_strsrch("<>|\t\v\n ", c) && (*singl != -1 && *doubl != -1))
		return (0);
	else
		return (1);
}

void	chang_status(t_env *envp)
{
	if (g_var_f.exit_s != 0)
	{
		envp->exit_status = g_var_f.exit_s;
		g_var_f.exit_s = 0;
	}
}

int	ft_minishell(t_data *data, t_env **envp, char *len)
{
	t_lexer	*lexer;

	if (len == NULL)
		return (1);
	chang_status(*envp);
	(*envp)->env = get_envp(*envp, (*envp)->env);
	add_history(len);
	if (!check_quote(len))
	{
		printf("syntax error\n");
		free(len);
	}
	else
	{
		lexer = NULL;
		ft_lexer(len, &lexer);
		data = ft_parsing(lexer, *envp);
		free(len);
		ft_execution(&data, (*envp)->env, envp);
		free_data(data);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	char	*len;
	t_env	*envp;

	envp = NULL;
	data = NULL;
	if (ac > 1 || !av)
	{
		printf("just one ergument\n");
		return (0);
	}
	set_env(env, &envp);
	signal(SIGINT, handle_signal1);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		len = readline(FG_YELLOW "minshell $ " FG_GREEN);
		if (ft_minishell(data, &envp, len))
			break ;
	}
	g_var_f.exit_s = envp->exit_status;
	free_envp(envp);
	rl_clear_history();
	printf("exit\n");
	exit(g_var_f.exit_s);
}
