/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:12:54 by ezhou             #+#    #+#             */
/*   Updated: 2024/06/04 16:55:12 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	*ft_get_label(char *variable)
{
	char	**aux;
	char	*label;

	aux = ft_split(variable, '=');
	if (!aux)
		return (NULL);
	label = ft_strdup(aux[0]);
	ft_free_char(aux);
	return (label);
}

char	*ft_get_value(char *variable)
{
	char	*value;
	int		i;

	value = NULL;
	i = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	i++;
	value = (char *)malloc(sizeof(char) * ft_strlen(variable + i) + 1);
	if (!value)
		return (NULL);
	ft_strlcpy(value, variable + i, ft_strlen(variable + i) + 1);
	return (value);
}

char	*ft_make_export_line(char *label, char *value)
{
	char	*result;
	char	*aux;

	if (!value || !value[0])
	{
		result = ft_strdup(label);
		if (!result)
			return (NULL);
		return (result);
	}
	result = ft_strjoin(label, "=");
	if (!result)
		return (NULL);
	aux = result;
	result = ft_strjoin(result, value);
	if (!result)
		return (free(aux), NULL);
	free(aux);
	return (result);
}

int	ft_has_args(char **arg)
{
	int	i;

	i = 1;
	if (arg[i])
	{
		if (arg[i][0])
			return (0);
		i++;
	}
	return (1);
}