/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addstring.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:43:24 by omar              #+#    #+#             */
/*   Updated: 2024/09/03 10:41:00 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_str(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	ft_copy(char **cmd, char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		cmd[i] = ft_strdup(str[i]);
		i++;
	}
	return (i);
}

char	**ft_addstring(char **str, t_lexer *lexer, t_env *envp)
{
	int		cont;
	t_var	var;

	var.j = 0;
	var.i = 0;
	if (str && !ft_strcmp(str[0], "export"))
		var.newstr = ft_expending_word(lexer->data, envp, 0);
	else
		var.newstr = ft_expending_word(lexer->data, envp, 1);
	cont = count_str(str) + count_str(var.newstr);
	var.cmd = ft_calloc(sizeof(char *), cont + 1);
	if (var.cmd == NULL)
		return (NULL);
	var.i = ft_copy(var.cmd, str);
	ft_copy(&var.cmd[var.i], var.newstr);
	ft_free1(str);
	ft_free1(var.newstr);
	return (var.cmd);
}
