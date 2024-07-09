/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:54:54 by rauferna          #+#    #+#             */
/*   Updated: 2024/07/02 20:34:08 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_check_program(char **args, int *k, int *i, t_cmd *cmd)
{
	char	*tmp;

	if (access(args[*k], F_OK) != 0)
	{
		ft_error_fnf(args[*k]);
		cmd->cmd_flag = -1;
		free(cmd->arg[*i]);
		return ;
	}
	if (access(args[*k], R_OK) != 0)
	{
		ft_error_perm(args[*k]);
		cmd->cmd_flag = -1;
		free(cmd->arg[*i]);
		return ;
	}
	cmd->cmd_path = ft_strdup(args[*k]);
	if (cmd->cmd_path == NULL)
		ft_exit_error("Malloc Error\n", 1, NULL);
	tmp = cmd->arg[*i];
	cmd->arg[(*i)++] = ft_strdup(args[*k]);
	if (cmd->arg[(*i) - 1] == NULL)
		ft_exit_error("Malloc Error\n", 1, NULL);
	free(tmp);
	cmd->cmd_flag = 1;
}

static void	fill_and_free_args(char **args, int *i, int *k, t_cmd *cmd)
{
	char	*tmp;

	tmp = NULL;
	if (cmd->file_flag != 0)
	{
		tmp = args[*k];
		cmd->arg[(*i)++] = ft_strdup(args[*k]);
		free(tmp);
		tmp = NULL;
	}
	else
	{
		tmp = cmd->arg[*i];
		cmd->arg[(*i)++] = ft_strdup(args[*k]);
		free(tmp);
		tmp = NULL;
	}
}

static void	ft_check_rest(char **args, int *i, int *k, t_cmd *cmd)
{
	if ((cmd->cmd_flag <= -1 || cmd->file_flag == -1 || cmd->two_points == 1))
	{
		free(cmd->arg[*k]);
		cmd->arg[*i] = NULL;
	}
	else if ((args[*k][0] == ':' || args[*k][0] == '!')
		&& !args[*k][1] && cmd->cmd_flag == 0)
	{
		free(cmd->arg[*k]);
		cmd->arg[*i] = NULL;
		cmd->two_points = 1;
	}
	else if (ft_strncmp(args[*k], "./", 2) == 0 && cmd->cmd_flag == 0)
		ft_check_program(args, k, i, cmd);
	else if (cmd->cmd_flag == 0)
		ft_check_cmd(args, i, k, cmd);
	else if (cmd->cmd_flag == 1)
		fill_and_free_args(args, i, k, cmd);
	else
	{
		ft_error_syntax(args[*k]);
		cmd->cmd_flag = -1;
	}
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

void	ft_process_args(t_cmd *cmd, t_data *data, char **args)
{
	int		i;
	int		k;
	int		redirect;

	i = 0;
	k = 0;
	check_first(args, &k, cmd);
	if (cmd->cmd_flag == -1)
		return ;
	while (k <= cmd->num_i)
	{
		redirect = 0;
		if ((ft_strchr(cmd->arg[k], '$') != NULL && cmd->type[k] != 's'
				&& cmd->type[k] != 'h') || cmd->type[k] == 'v')
			cmd->arg[k] = ft_copy_env(cmd->arg[k], &k, cmd);
		if ((ft_strchr(cmd->arg[k], '<') != NULL
				|| ft_strchr(cmd->arg[k], '>') != NULL) && cmd->type[k] != 'd'
			&& cmd->type[k] != 's')
			cmd->file_flag = ft_check_redirections(&k, cmd, data, &redirect);
		if (redirect >= 0)
			ft_check_rest(cmd->arg, &i, &k, cmd);
		k++;
	}
	cmd->arg[i] = NULL;
}
