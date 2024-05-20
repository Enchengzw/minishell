/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:26:29 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/08 13:56:51 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_builtins(t_cmd *cmd, t_data *data)
{
	int	exit;

	ft_set_redirections(cmd);
	exit = ft_redirect(cmd);
	if (ft_strcmp(cmd->arg[0], "cd") == 0 && !exit)
		exit = ft_cd(&cmd);
	else if (ft_strcmp(cmd->arg[0], "echo") == 0 && !exit)
		exit = ft_echo(cmd->arg);
	else if (ft_strcmp(cmd->arg[0], "env") == 0 && !exit)
		exit = ft_env(&cmd);
	else if (ft_strcmp(cmd->arg[0], "exit") == 0 && !exit) // WARNING
		exit = ft_exit(cmd, data);
	else if (ft_strcmp(cmd->arg[0], "export") == 0 && !exit)
		exit = ft_export(&cmd);
	else if (ft_strcmp(cmd->arg[0], "pwd") == 0 && !exit)
		exit = ft_pwd();
	else if (ft_strcmp(cmd->arg[0], "unset") == 0 && !exit)
		exit = ft_unset(&cmd);
	if (cmd->next && ft_close(&(cmd->fds->pipe[1])))
		return (ERROR);
 	if (cmd->previous && ft_close(&(cmd->previous->fds->pipe[0])))
		return (ERROR);
	if (ft_restore_io(cmd))
		return (ft_putstr_fd("Out of resources\n", STDERR), ERROR);
	return (exit);
}

int	ft_list_size(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count +=1;
		cmd = cmd->next;
	}
	return (count);
}