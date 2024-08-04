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

void	apend_in_struct(t_lexer **lexer, char *str, t_token token,t_env *envp)
{
	t_lexer	*new_lexer;
	int		len;

	len = ft_strlen(str);
	//if (ft_strchr(str,'$'))
	str = ft_expending(*lexer, str, &token,envp);
	new_lexer = *lexer;
	if (token == inredire && len == 2)
		token = herduc;
	else if (token == outredire && len == 2)
		token = apenred;
	new_lexer = malloc(sizeof(t_lexer));
	if (new_lexer == NULL)
		return ;
	new_lexer->data = str;
	new_lexer->token = token;
	new_lexer->next = NULL;
	new_lexer->prev = NULL;
	ft_lstadd_back(lexer, new_lexer);
}