/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:12:54 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/27 12:31:10 by ezhou            ###   ########.fr       */
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
	char	**aux;
	char	*value;
	int		length;
	int		i;

	value = NULL;
	i = 1;
	length = 0;
	aux = ft_split(variable, '=');
	if (!aux)
		return (NULL);
	while (aux[i])
	{
		length = ft_strlen(value) + ft_strlen(aux[i]) + 1;
		value = ft_strjoin_alt(value, aux[i], length);
		if (!value)
			return (ft_free_char(aux), NULL);
		i++;
	}
	ft_free_char(aux);
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
