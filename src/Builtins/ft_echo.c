/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:06:46 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/07 11:14:45 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_print_echo(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i + 1] && str[i] == '$' && str[i + 1] == '?')
		{
			ft_printf("%d", g_exit_code);
			i++;
		}
		else
			ft_printf("%c", str[i]);
		i++;
	}
}

int	ft_echo(char **args)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	if (ft_dpointer_size(args) < 1)
		return (SUCCESS);
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_print_echo(args[i]);
		if (args[i + 1] && args[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	return (SUCCESS);
}
