/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:47:52 by oait-bou          #+#    #+#             */
/*   Updated: 2024/09/05 11:16:41 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_shlvl(t_env *envp)
{
	char	*valeu;
	int		shl;

	while (envp)
	{
		if (!ft_strcmp(envp->var, "SHLVL"))
		{
			shl = ft_atoi(&envp->value[1]) + 1;
			if (shl >= 1000)
			{
				printf("warning: shell level (%d) too high\n", shl);
				shl = 1;
			}
			free(envp->value);
			valeu = ft_itoa(shl);
			envp->value = ft_strjoinn("=", valeu);
			free(valeu);
			return ;
		}
		envp = envp->next;
	}
	ft_setenv("SHLVL=1", &envp);
}

void	add_path(t_env **envp)
{
	t_env	*node;

	node = ft_calloc(sizeof(t_env), 1);
	if (node == NULL)
		return ;
	node->var = ft_strdup("PATH");
	node->value = ft_strdup("=/nfs/homes/oait-bou/bin:/usr/local/sbin:/usr/local/bin\
		:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin");
	node->egnor = 1;
	ft_lstadd_backenv(envp, node);
}

void	set_env(char **env, t_env **envp)
{
	int		i;
	char	*str;
	char	*s;

	i = -1;
	*envp = ft_calloc (sizeof(t_env),1);
	if (*envp == NULL)
		return;
	if (*env == NULL)
	{
		s = getcwd(NULL, 0);
		add_path(envp);
		str = ft_strjoinn("PWD=", s);
		ft_setenv(str, envp);
		free(str);
		free(s);
		ft_setenv("SHLVL=1", envp);
		ft_setenv("OLDPWD", envp);
		ft_setenv("_=/usr/bin/env", envp);
		return ;
	}
	while (env[++i])
		ft_setenv(env[i], envp);
	change_shlvl(*envp);
}
