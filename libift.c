/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libift.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-bou <oait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:45:36 by omar              #+#    #+#             */
/*   Updated: 2024/09/05 10:46:10 by oait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum(int c)
{
	if (c == '_')
		return (1);
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if (c == '_')
		return (1);
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

char	*skip_char(char *s, char c)
{
	int		n;
	char	*str;

	n = 0;
	while (s[n] && s[n] != c)
		n++;
	str = ft_calloc(sizeof(char), n + 1);
	if (!str)
		return (NULL);
	ft_strncpy(str, s, n);
	return (str);
}

char	*ft_strncpy(char *dest, char *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
