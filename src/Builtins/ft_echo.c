/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:06:46 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/01 13:00:25 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_echo(char **args)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	if (ft_dpointer_size(args) > 1)
	{
		while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
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
	}
	if (!flag)
		write(1, "\n", 1);
	return (SUCCESS);
}
