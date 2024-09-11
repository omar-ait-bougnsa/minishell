/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:45:14 by omar              #+#    #+#             */
/*   Updated: 2024/09/03 14:54:16 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_backenv(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!env || !new)
		return ;
	if (*env)
	{
		tmp = *env;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*env = new;
}

char	*ft_getvar(char *str)
{
	int		i;
	char	*newstr;
	int		n;

	i = 0;
	n = 0;
	while (str[n] && str[n] != '=' && str[n] != '+')
		n++;
	newstr = ft_calloc(sizeof(char), n + 1);
	if (newstr == NULL)
		return (NULL);
	n = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '+')
			newstr[n++] = str[i];
		i++;
	}
	newstr[n] = '\0';
	return (newstr);
}

int	check_var(char *var, char *value, t_env *envp)
{
	while (envp)
	{
		if (!ft_strcmp(envp->var, var))
		{
			if (ft_strchr(value, '='))
			{
				if (envp->value)
					free(envp->value);
				envp->value = value;
				envp->egnor = 0;
			}
			free(var);
			return (1);
		}
		envp = envp->next;
	}
	return (0);
}

void	ft_setenv(char *env, t_env **envp)
{
	char	*valeu;
	char	*var;
	t_env	*newenv;

	var = ft_getvar(env);
	valeu = ft_strsrch(env, '=');
	if (valeu)
		valeu = ft_strdup(valeu);
	if (check_var(var, valeu, *envp))
		return ;
	else
	{
		newenv = ft_calloc(sizeof(t_env), 1);
		if (!newenv)
			return ;
		newenv->value = valeu;
		newenv->var = var;
		ft_lstadd_backenv(envp, newenv);
	}
}
