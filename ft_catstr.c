/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_catstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:45:11 by omar              #+#    #+#             */
/*   Updated: 2024/09/01 11:50:37 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_word_expand(char *str,t_var *var)
{
	int i;
	i = 0;
	var->flg = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '$')
		{
			var->flg = 1;
			return ;
		}
		i++;
	}
}
void	free_lexer(t_lexer *lexer)
{
	t_lexer	*next;

	next = lexer;
	if (!lexer)
		return ;
	while (next != NULL)
	{
		lexer = next->next;
		if (next->data)
			free(next->data);
		free(next);
		next = lexer;
	}
}

char	**ft_catstr(char **str, char **str1)
{
	t_var	var;

	var.i = 0;
	var.j = -1;
	var.n = count_str(str) + count_str(str1);
	var.newstr = ft_calloc(sizeof(char *), var.n + 1);
	if (!var.newstr)
		return (NULL);
	while (str && str[var.i])
		var.newstr[++var.j] = ft_strdup(str[var.i++]);
	if (var.j == -1)
		var.j = 0;
	var.var = ft_strjoinn(var.newstr[var.j], str1[0]);
	if (var.newstr[var.j])
		free(var.newstr[var.j]);
	var.newstr[var.j] = var.var;
	var.j++;
	var.i = 1;
	while (str1 && str1[var.i])
		var.newstr[var.j++] = ft_strdup(str1[var.i++]);
	ft_free1(str);
	ft_free1(str1);
	return (var.newstr);
}
