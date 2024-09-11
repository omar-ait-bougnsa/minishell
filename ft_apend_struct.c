/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apend_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:44:02 by omar              #+#    #+#             */
/*   Updated: 2024/09/03 10:26:50 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*temp;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		temp = *lst;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new;
		new->prev = temp;
	}
	else
		*lst = new;
}

void	apend_in_struct(t_lexer **lexer, char *str, int type)
{
	t_lexer	*new_lexer;
	int		len;

	len = ft_strlen(str);
	if (type == IN_RED && len == 2)
		type = HE_RDUC;
	else if (type == OUT_RED && len == 2)
		type = AP_END;
	new_lexer = ft_calloc(sizeof(t_lexer), 1);
	if (new_lexer == NULL)
		return ;
	new_lexer->data = str;
	new_lexer->type = type;
	ft_lstadd_back(lexer, new_lexer);
}
