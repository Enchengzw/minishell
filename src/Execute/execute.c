/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:27:08 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/02 13:17:38 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_restore_io(t_cmd *cmd)
{
	if (dup2((cmd->fds->std_in), STDIN_FILENO) == -1)
		return (ERROR);
	if (dup2((cmd->fds->std_out), STDOUT_FILENO) == -1)
		return (ERROR);
	return (SUCCESS);
}

int	ft_redirect(t_cmd *cmd)
{
	if (cmd->fds->infile >= 0)
	{
		if (dup2(cmd->fds->infile, STDIN_FILENO) == -1)
		{
			ft_putstr_fd("Dup2 ErroIr\n", 2);
			return (ERROR);
		}
		close(cmd->fds->infile);
	}
	if (cmd->fds->outfile >= 0)
	{
		if (dup2(cmd->fds->outfile, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("Dup2 Error\n", 2);
			return (ERROR);
		}
		close(cmd->fds->outfile);
	}
	return (SUCCESS);
}

int	execute_builtins(t_cmd *cmd)
{
	int	exit;

	if (ft_strcmp(cmd->arg[0], "cd") == 0)
		exit = ft_cd(&cmd);
	else if (ft_strcmp(cmd->arg[0], "echo") == 0)
		exit = ft_echo(cmd->arg);
	else if (ft_strcmp(cmd->arg[0], "env") == 0)
		exit = ft_env(&cmd);
	else if (ft_strcmp(cmd->arg[0], "exit") == 0)//WARNING
		exit = ft_exit(cmd, cmd->arg);
	else if (ft_strcmp(cmd->arg[0], "export") == 0)
		exit = ft_export(&cmd);
	else if (ft_strcmp(cmd->arg[0], "pwd") == 0)
		exit = ft_pwd();
	else if (ft_strcmp(cmd->arg[0], "unset") == 0)
		exit = ft_unset(&cmd);
	if (ft_restore_io(cmd))
			return (ft_putstr_fd("Out of resources\n", STDERR), ERROR);
	return (exit);
}

int	ft_actions(pid_t pid, t_cmd *cmd)
{
	if (pid == 0)
	{
		ft_child_signals();
		if (execve(cmd->cmd_path, cmd->arg, *(cmd->env->env)) == -1)
			return (ft_putstr_fd("Error executing execve\n", STDERR), ERROR);
	}
	else
	{
		waitpid(pid, &g_exit_code, 0);
		if (ft_restore_io(cmd))
			return (ft_putstr_fd("Out of resources\n", STDERR), ERROR);
	}
	return (SUCCESS);
}

int	ft_create_processes(t_data *data)
{
	pid_t	children;
	t_cmd	*temp;

	temp = data->cmd;
	while (temp)
	{
		if (ft_redirect(temp))
			return (ft_putstr_fd("Out of resources\n", STDERR), 12);
		if (temp->is_builtin == 1)
		{
			if (execute_builtins(temp))
				return (12);
		}
		else
		{
			children = fork();
			if (children == -1)
				return (ft_putstr_fd("Out of resources\n", STDERR), 12);
			if (ft_actions(children, temp))
				return (12);
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

int	ft_execute(t_data *data)
{
	int	code;

	code = ft_check_data(data);
	if (code != INT_MIN)
		return (code);
	if (ft_create_pipes(data) == ERROR)
		return (ft_putstr_fd("Not enough resources to create pipe\n", STDERR), 12);
	ft_link_io(data);
/* 	while (data->cmd)
	{
		ft_printf("INFILE: %d OUTFILE : %d PIPE[0] : %d PIPE [1] : %d INFILE_FLAG: %d \n", data->cmd->fds->infile, data->cmd->fds->outfile, data->cmd->fds->pipe[0], data->cmd->fds->pipe[1], data->cmd->infile_flag);
		data->cmd = data->cmd->next;
	} */
	return (ft_create_processes(data)); 
/*  	return (0);  */
}
