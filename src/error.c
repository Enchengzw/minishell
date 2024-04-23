/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:02:35 by ezhou             #+#    #+#             */
/*   Updated: 2024/04/23 18:00:34 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <errno.h>//no se si se puede usar

void	ft_exit_error(char *str, int n)
{
	ft_putstr_fd(str, STDERR);
//	ft_free_all(data)
	exit(n);
}

int	error_cnf(char *command)
{
	//ft_printf("minishell: %s: command not found\n", command);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(command, STDERR);
	ft_putstr_fd(": command not found\n", STDERR);
	return (1);
}

int	error_syntax(char *file)
{
	//ft_printf("bash: syntax error near unexpected token `%s'\n", args[*j]);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(file, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(strerror(errno), STDERR);
	ft_putstr_fd("\n", STDERR);
	return (1);
}

int	error_fnf(char *file)
{
	//ft_printf("minishell: %s: No such file or directory\n", file);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(file, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(strerror(errno), STDERR);
	ft_putstr_fd("\n", STDERR);
	return (1);
}
