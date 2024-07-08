/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:02:35 by ezhou             #+#    #+#             */
/*   Updated: 2024/06/04 20:18:29 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_exit_error(char *str, int n, t_data *data)
{
	ft_putstr_fd(str, STDERR);
	ft_free_all(data);
	exit(n);
}

int	ft_error_cnf(char *command)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (1);
}

int	ft_error_syntax(char *file)
{
	ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

int	ft_error_fnf(char *file)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

int	ft_error_perm(char *file)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	return (1);
}
