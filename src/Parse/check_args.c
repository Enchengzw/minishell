/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:54:54 by rauferna          #+#    #+#             */
/*   Updated: 2024/06/04 20:18:46 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_check_program(char **args, int *k, int *i, t_cmd *cmd)
{
	if (access(args[*k], F_OK) != 0)
	{
		ft_error_fnf(args[*k]);
		cmd->file_flag = -1;
		return ;
	}
	if (access(args[*k], R_OK) != 0)
	{
		write(2, "minishell: ", 11);
		write(2, args[*k], ft_strlen(args[*k]));
		write(2, ": Permission denied\n", 20);
		cmd->file_flag = -1;
		return ;
	}
	cmd->cmd_path = ft_strdup(args[*k]);
	cmd->arg[(*i)++] = ft_strdup(args[*k]);
	cmd->cmd_flag = 1;
}

static void	ft_check_rest(char **args, int *i, int *k, t_cmd *cmd)
{
	int	start;

	start = 0;
	if ((args[*k][0] == ':' || args[*k][0] == '!')
		&& !args[*k][1] && cmd->cmd_flag == 0)
	{
		cmd->two_points = 1;
		return ;
	}
	if (ft_strncmp(args[*k], "./", 2) == 0)
		ft_check_program(args, k, i, cmd);
	else if (cmd->cmd_flag == 0)
		ft_check_cmd(args, i, k, cmd);
	else if (cmd->cmd_flag == 1)
	{
		while (args[*k] && args[*k][start] == ' ')
			start++;
		if ((*k > 0 && args[*k - 1][0] == '>') || args[*k - 1][0] == '<')
			return ;
		else
			cmd->arg[(*i)++] = ft_copy_char(args[*k], cmd);
	}
	else
		ft_error_syntax(args[*k]);
}

static	void	check_first(char **args, int *k, t_cmd *cmd)
{
	if (cmd->arg[*k] == NULL)
	{
		if (args[*k + 1] != NULL)
			ft_error_syntax("|");
		cmd->cmd_flag = -1;
	}
}

char	**ft_process_args(t_cmd *cmd, t_data *data, char **args)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	check_first(args, &k, cmd);
	while (cmd->arg[k])
	{
		if (cmd->cmd_flag == -1 || cmd->file_flag == -1 || cmd->two_points == 1)
			break ;
		if (ft_strchr(cmd->arg[k], '<') != NULL
			|| ft_strchr(cmd->arg[k], '>') != NULL)
			cmd->file_flag = ft_check_redirections(cmd->arg, k, cmd, data);
		if (cmd->redirect_then >= 0)
			ft_check_rest(cmd->arg, &i, &k, cmd);
		if (cmd->arg[k] != NULL)
			k++;
	}
	cmd->arg[i] = NULL;
	return (cmd->arg);
}
