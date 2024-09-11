/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:45:51 by omar              #+#    #+#             */
/*   Updated: 2024/09/03 10:28:08 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apend_to_data(t_data **data, t_file **file, char ***cmd)
{
	t_data	*newdata;
	t_data	*tmp;

	newdata = ft_calloc(sizeof(t_data), 1);
	if (newdata == NULL)
		return ;
	newdata->cmd = *cmd;
	newdata->file = *file;
	*file = NULL;
	tmp = *data;
	if (*data)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = newdata;
	}
	else
		*data = newdata;
	*cmd = NULL;
}

t_data	*ft_parsing(t_lexer *lexer, t_env *envp)
{
	t_data	*data;
	t_var	var;

	var.new = lexer;
	var.cmd = NULL;
	data = NULL;
	if (lexer == NULL)
		return (NULL);
	var.file = NULL;
	while (lexer)
	{
		if (lexer->type == WO_RD && lexer->prev == NULL)
			var.cmd = ft_addstring(var.cmd, lexer, envp);
		else if (lexer->type == WO_RD && lexer->prev->type != WO_RD
			&& lexer->prev->type != PI_PE)
			apend_to_file(lexer, lexer->prev->type, &var.file, envp);
		else if (lexer->type == PI_PE)
			apend_to_data(&data, &var.file, &var.cmd);
		else if (lexer->type == WO_RD)
			var.cmd = ft_addstring(var.cmd, lexer, envp);
		lexer = lexer->next;
	}
	apend_to_data(&data, &var.file, &var.cmd);
	free_lexer(var.new);
	return (data);
}
