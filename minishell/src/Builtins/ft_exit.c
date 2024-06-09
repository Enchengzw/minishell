/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:38:47 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/27 12:42:11 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_print_error(char *variable, int *exit_code)
{
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(variable, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	*exit_code = 255;
}

static int	ft_only_digits(char *str, int *exit)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_print_error(str, exit);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_exit(t_cmd *cmd, t_data *start)
{
	int	code;

	cmd->num_arg = ft_dpointer_size(cmd->arg);
	ft_putstr_fd("exit\n", 2);
	if (cmd->num_arg > 2)
		return (ft_putstr_fd("exit: too many arguments\n", 2), ERROR);
	if (cmd->num_arg <= 1)
		code = start->exit_code;
	else
	{
		if (ft_only_digits(cmd->arg[1], &code) == 1)
			code = ft_atol(cmd->arg[1]);
	}
	if (code > 255)
		code = code % 256;
	ft_free_all(start);
	exit(code);
}
