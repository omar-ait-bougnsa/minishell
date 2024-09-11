/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expending.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:44:45 by omar              #+#    #+#             */
/*   Updated: 2024/09/03 10:38:24 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_str(char *str, t_var *var)
{
	if (str[var->i] == '\'' && var->dobqot == 1)
		var->i++;
	else if (str[var->i] == '\"' && var->sinqot == 1)
		var->i++;
	else if (str[var->i] == '$' && var->sinqot == 1 && var->dobqot == 1
		&& (str[var->i + 1] == '\"' || str[var->i + 1] == '\''))
		var->i++;
	else
	{
		var->newstr[var->n] = apend_char_str(var->newstr[var->n], str[var->i]);
		var->i += 1;
	}
}

void	expand_var(t_var *var, t_env *envp, int flag)
{
	char	*path;
	char	**str1;

	path = ft_getenv(envp, var->var);
	free(var->var);
	if (path && var->sinqot == 1 && var->dobqot == 1 &&(flag || var->flg))
	{
		str1 = ft_split_it(path);
		var->newstr = ft_catstr(var->newstr, str1);
		var->n = count_str(var->newstr) - 1;
	}
	else
	{
		var->s = ft_strjoinn(var->newstr[var->n], path);
		free(var->newstr[var->n]);
		var->newstr[var->n] = var->s;
	}
}

void	other_condition(t_var *var, char *str, t_env *envp, int flg)
{
	if (str[var->i] == '$' && var->sinqot == 1 && ft_isalpha(str[var->i + 1]))
	{
		while (str[++var->i] && ft_isalnum(str[var->i]))
			var->var = apend_char_str(var->var, str[var->i]);
	}
	else if (str[var->i] == '$' && ft_isdigit(str[var->i + 1]))
		var->i += 2;
	else if (str[var->i] != '\0')
		add_to_str(str, var);
	if (var->var != NULL)
	{
		expand_var(var, envp, flg);
	}
	if (!var->newstr[0] && (var->dobqot == -1 || var->sinqot == -1))
		var->newstr[0] = apend_char_str(var->newstr[0], '\0');
}

int	ft_exit_status(t_var *var, t_env *envp)
{
	char	*str;
	char	*s;

	s = ft_itoa(envp->exit_status);
	str = ft_strjoinn(var->newstr[var->n], s);
	if (var->newstr)
		free(var->newstr[var->n]);
	free(s);
	var->newstr[var->n] = str;
	return (2);
}

char	**ft_expending_word(char *str, t_env *envp, int flg)
{
	t_var	var;

	var.i = 0;
	var.sinqot = 1;
	var.dobqot = 1;
	var.n = 0;
	var.newstr = ft_calloc(sizeof(char *), 2);
	if (!var.newstr)
		return (NULL);
	check_word_expand (str,&var);
	while (str[var.i])
	{
		var.var = NULL;
		if (str[var.i] == '\'' && var.dobqot == 1)
			var.sinqot *= (-1);
		else if (str[var.i] == '\"' && var.sinqot == 1)
			var.dobqot *= (-1);
		if (str[var.i] == '$' && str[var.i + 1] == '\0')
			var.newstr[var.n] = apend_char_str(var.newstr[var.n], str[var.i++]);
		else if (str[var.i] == '$' && str[var.i + 1] == '?' && var.sinqot == 1)
			var.i += ft_exit_status(&var, envp);
		else
			other_condition(&var, str, envp, flg);
	}
	return (var.newstr);
}
