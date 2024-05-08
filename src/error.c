/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:02:35 by ezhou             #+#    #+#             */
/*   Updated: 2024/03/22 15:35:44 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_exit_error(char *str, int n, t_data *data)
{
	ft_putstr_fd(str, STDERR);
//	ft_free_all(data)
	exit(n);
}

int	error_cnf(char *command)
{
	//ft_printf("minishell: %s: command not found\n", command);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (1);
}

int	error_syntax(char *file)
{
	//ft_printf("bash: syntax error near unexpected token `%s'\n", args[*j]);
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

int	error_fnf(char *file)
{
	//ft_printf("minishell: %s: No such file or directory\n", file);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}
