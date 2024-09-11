/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:44:58 by omar              #+#    #+#             */
/*   Updated: 2024/09/02 11:11:39 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->value)
			i++;
		env = env->next;
	}
	return (i);
}

char	*ft_getenv(t_env *env, char *str)
{
	char	*s;

	s = NULL;
	if (!str)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->var, str))
			s = env->value;
		env = env->next;
	}
	if (s == NULL)
		return (NULL);
	s = &s[1];
	if (*s == '\0')
		return (NULL);
	return (s);
}

char	**get_envp(t_env *envp, char **env)
{
	int		cont;
	char	**str;
	int		i;

	i = 0;
	ft_free1(env);
	cont = count_env(envp);
	str = ft_calloc(sizeof(char *), cont + 1);
	if (str == NULL)
		return (NULL);
	while (envp)
	{
		if (envp->value)
		{
			str[i] = ft_strjoinn(envp->var, envp->value);
			i++;
		}
		envp = envp->next;
	}
	return (str);
}
