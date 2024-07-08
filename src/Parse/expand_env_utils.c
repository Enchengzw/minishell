/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:35:00 by rauferna          #+#    #+#             */
/*   Updated: 2024/07/07 18:45:00 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_special_character(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == ','
		|| c == '{' || c == '}' || c == '[' || c == ']' || c == '"'
		|| c == '\'' || c == '\\' || c == '#' || c == '&' || c == '*'
		|| c == '?' || c == '/' || c == ':' || c == '@' || c == '='
		|| c == '$' || c == '%' || c == '-' || c == '~' || c == '|')
		return (1);
	else
		return (0);
}

char	*ft_strjoin_allocs1(char *s1, char *s2, int num)
{
	char	*str;

	if (!s1)
	{
		s1 = ft_calloc(1, sizeof(char));
		if (!s1)
			return (NULL);
	}
	if (!s2)
	{
		s2 = ft_calloc(1, sizeof(char));
		if (!s2)
			return (NULL);
	}
	str = ft_strjoin(s1, s2);
	if (!str)
		return (NULL);
	if (num == 1 || num == 0)
		free(s1);
	s1 = NULL;
	if (num == 0 || num == 2)
		free(s2);
	s2 = NULL;
	return (str);
}
