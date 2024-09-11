/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apend_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:43:29 by omar              #+#    #+#             */
/*   Updated: 2024/09/05 10:39:05 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_qout(char *str)
{
	t_var	var;
	char	*newstr;

	var.i = 0;
	var.sinqot = 1;
	var.dobqot = 1;
	newstr = NULL;
	while (str[var.i])
	{
		if (str[var.i] == '\'' && var.dobqot == 1)
			var.sinqot *= (-1);
		if (str[var.i] == '\"' && var.sinqot == 1)
			var.dobqot *= (-1);
		if (str[var.i] == '\'' && var.dobqot == 1)
			;
		else if (str[var.i] == '\"' && var.sinqot == 1)
			;
		else
			newstr = apend_char_str(newstr, str[var.i]);
		var.i++;
	}
	if (newstr == NULL)
		newstr = apend_char_str(newstr, '\0');
	return (newstr);
}

void	ft_lstadd_back1(t_file **file, t_file *new)
{
	t_file	*tmp;

	if (!file || !new)
		return ;
	if (*file)
	{
		tmp = *file;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*file = new;
}

void	ft_ambiguous(char **namfile, t_file **file, t_file *newfile, char *s)
{
	ft_free1(namfile);
	newfile->file = s;
	newfile->ambiguous = 1;
	ft_lstadd_back1(file, newfile);
}

void	type_file(int type, t_file *newfile)
{
	if (type == IN_RED)
		newfile->infile = 1;
	else if (type == OUT_RED)
		newfile->outfile = 1;
	else if (type == HE_RDUC)
		newfile->herdoc = 1;
	else if (type == AP_END)
		newfile->apend = 1;
}

void	apend_to_file(t_lexer *lexer, int type, t_file **file, t_env *envp)
{
	t_file	*newfile;
	char	**namfile;

	newfile = ft_calloc(sizeof(t_file), 1);
	if (newfile == NULL)
		return ;
	if (ft_strsrch(lexer->data, '\'') || ft_strsrch(lexer->data, '\"'))
		newfile->expand = 1;
	if (type != HE_RDUC)
		namfile = ft_expending_word(lexer->data, envp, 1);
	else
	{
		namfile = ft_calloc(sizeof(char *), 2);
		namfile[0] = remove_qout(lexer->data);
	}
	if (!namfile[0] || count_str(namfile) > 1)
	{
		ft_ambiguous(namfile, file, newfile, ft_strdup(lexer->data));
		return ;
	}
	type_file(type, newfile);
	newfile->file = namfile[0];
	free(namfile);
	ft_lstadd_back1(file, newfile);
}
