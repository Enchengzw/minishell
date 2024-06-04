/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:06:46 by ezhou             #+#    #+#             */
/*   Updated: 2024/06/04 17:32:47 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_is_valid_flag(char	*argument)
{
	int	i;

	i = 0;
	if (argument[i] != '-')
		return (0);
	i++;
	while (argument[i])
	{
		if (argument[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	if (ft_dpointer_size(args) < 1)
		return (SUCCESS);
	while (args[i] && ft_is_valid_flag(args[i]))
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] && args[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	return (SUCCESS);
}
