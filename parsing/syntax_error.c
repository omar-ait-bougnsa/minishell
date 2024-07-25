#include "minishell.h"

int	print_error(t_lexer **lexer, char *str, char *str1)
{
	if (str1 && ft_strlen(str1) > 1)
		printf("%s`%c%c'\n", str, str1[0], str1[1]);
	else if (str1)
		printf("%s`%c'\n", str, str1[0]);
	else
		printf("%s\n", str);
	// free(*lexer);
	*lexer = NULL;
	return (0);
}
int	syntax_error(t_lexer **lexer)
{
	t_lexer	*newlexer;

	newlexer = *lexer;
	if (!(*lexer))
		return (0);
	while (newlexer->next)
	{
		if (newlexer->token == error)
		{
			printf("error22\n");
			return (0);
		}
		if (newlexer->token != word && newlexer->token != herduc
			&& newlexer->token != apenred)
		{
			if (ft_strlen(newlexer->data) > 1)
				return (print_error(lexer,
						"syntax error near unexpected token ", newlexer->data));
		}
		newlexer = newlexer->next;
		if (newlexer->token == error)
		{
			printf("error22\n");
			return (0);
		}
		if (newlexer->token == pipe1 && (newlexer->prev == NULL || newlexer->prev->token != word))
			return (print_error(lexer, "syntax error near unexpected token",
					newlexer->data));
		if (newlexer->prev->token != word && newlexer->prev->token != pipe1
			&& newlexer->token != word)
			return (print_error(lexer, "syntax error near unexpected token",
					newlexer->data));
	}
	if (newlexer->token != word && ft_strlen(newlexer->data) >= 2)
		return (print_error(lexer, "syntax error near unexpected token",
				newlexer->data));
	else if (newlexer->token == pipe1)
		return (print_error(lexer, "syntax error near unexpected token ",
				newlexer->data));
	else if (newlexer->token != word)
		return (print_error(lexer,
				"syntax error near unexpected token `newline'", NULL));
	return (0);
}
