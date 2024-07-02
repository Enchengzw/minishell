/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:52:20 by ezhou             #+#    #+#             */
/*   Updated: 2024/06/27 20:55:54 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_check_double_greather(char **args, char *res, int i, t_cmd *cmd)
{
	if (ft_strlen(res) == 2)
		cmd->fds->outfile = ft_openfile(args[i + 1], 3);
	else
		cmd->fds->outfile = ft_openfile(res + 2, 3);
	cmd->outfile_flag = 1;
}

void	ft_get_exit_code(int pid, int *status, t_data *data)
{
	int	pid_check;

	while (1)
	{
		pid_check = waitpid(pid, status, 0);
		if (pid_check > 0)
			break ;
		data->is_interrupted = 1;
	}
}

void	ft_free_redirection_space(char *arg, char **arg2)
{
	if (ft_strcmp(arg, ">>") == 0 || ft_strcmp(arg, "<<") == 0
		|| ft_strncmp(arg, ">", 2) == 0 || ft_strcmp(arg, "<") == 0)
	{
		free(*arg2);
		(*arg2) = NULL;
	}
	else if (ft_strncmp(arg, ">>>", 3) == 0 || ft_strncmp(arg, "<<<", 3) == 0)
	{
		free(*arg2);
		(*arg2) = NULL;
	}
}