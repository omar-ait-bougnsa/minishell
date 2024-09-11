/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_her.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:49:01 by oait-bou          #+#    #+#             */
/*   Updated: 2024/09/05 10:23:59 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_tostr(char *str, t_var var, int *i)
{
	{
		var.s = apend_char_str(var.s, str[*i]);
		*i += 1;
	}
	return (var.s);
}

void	other_conditio(t_var *var, char *str, t_env *envp)
{
	char	*path;
	char	*s;

	s = NULL;
	if (str[var->i] == '$' && ft_isalpha(str[var->i + 1]))
	{
		while (str[++var->i] && ft_isalnum(str[var->i]))
			var->var = apend_char_str(var->var, str[var->i]);
	}
	else if (str[var->i] == '$' && ft_isdigit(str[var->i + 1]))
		var->i += 2;
	else if (str[var->i] != '\0')
	{
		var->s = apend_char_str(var->s, str[var->i]);
		var->i += 1;
	}
	if (var->var != NULL)
	{
		path = ft_getenv(envp, var->var);
		free(var->var);
		s = ft_strjoinn(var->s, path);
		if (var->s)
			free(var->s);
		var->s = s;
	}
}

int	ft_exit_statu(t_var *var, t_env *envp)
{
	char	*str;
	char	*s;

	s = ft_itoa(envp->exit_status);
	str = ft_strjoinn(var->s, s);
	if (var->s)
		free(var->s);
	free(s);
	var->s = str;
	return (2);
}

char	*expending_herd(char *str, t_env *envp)
{
	t_var	var;

	var.i = 0;
	var.s = NULL;
	while (str[var.i])
	{
		var.var = NULL;
		if (str[var.i] == '$' && str[var.i + 1] == '\0')
			var.s = apend_char_str(var.s, str[var.i++]);
		if (str[var.i] == '$' && str[var.i + 1] == '?')
			var.i += ft_exit_statu(&var, envp);
		if (str[var.i] == '\0')
			break ;
		other_conditio(&var, str, envp);
	}
	free(str);
	return (var.s);
}
