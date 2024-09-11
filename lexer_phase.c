/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_phase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:45:32 by omar              #+#    #+#             */
/*   Updated: 2024/09/03 10:36:01 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_outred(t_lexer **lexer, char *len)
{
	int		i;
	char	*str;

	i = 0;
	while (len[i] == '>')
		i++;
	str = malloc(i + 1);
	if (str == NULL)
		return (0);
	ft_strncpy(str, len, i);
	apend_in_struct(lexer, str, OUT_RED);
	return (i);
}

int	ft_inreder(t_lexer **lexer, char *len)
{
	int		i;
	char	*str;

	i = 0;
	while (len[i] == '<')
		i++;
	str = malloc(i + 1);
	if (str == NULL)
		return (0);
	ft_strncpy(str, len, i);
	apend_in_struct(lexer, str, IN_RED);
	return (i);
}

int	ft_pipe(t_lexer **lexer, char *len)
{
	int		i;
	char	*str;

	i = 0;
	while (len[i] == '|')
		i++;
	str = malloc(i + 1);
	if (str == NULL)
		return (0);
	ft_strncpy(str, len, i);
	apend_in_struct(lexer, str, PI_PE);
	return (i);
}

int	ft_word(t_lexer **lexer, char *len)
{
	int		singl;
	int		doubl;
	int		i;
	char	*str;

	i = 0;
	singl = 1;
	doubl = 1;
	while (len[i] && ft_token(len[i], &singl, &doubl))
		i++;
	str = malloc(i + 1);
	if (str == NULL)
		return (0);
	str = ft_strncpy(str, len, i);
	apend_in_struct(lexer, str, WO_RD);
	return (i);
}

void	ft_lexer(char *len, t_lexer **lexer)
{
	int	i;

	i = 0;
	*lexer = NULL;
	while (len[i])
	{
		if (len[i] == '>')
			i += ft_outred(lexer, &len[i]);
		else if (len[i] == '<')
			i += ft_inreder(lexer, &len[i]);
		else if (len[i] == '|')
			i += ft_pipe(lexer, &len[i]);
		else if (is_whitespace(len[i]))
			i++;
		else
			i += ft_word(lexer, &len[i]);
	}
	syntax_error(lexer);
}
