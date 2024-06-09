/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 21:44:53 by rauferna          #+#    #+#             */
/*   Updated: 2024/06/04 20:16:07 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	pre_check(char **args, int *k)
{
	if (*k > 0 && (((strcmp(args[*k - 1], "<") == 0
					|| strcmp(args[*k - 1], "<<") == 0))
			|| (strcmp(args[*k - 1], "<") == 0
				|| strcmp(args[*k - 1], "<<") == 0)))
		return (1);
	return (0);
}

void	ft_check_cmd(char **args, int *i, int *k, t_cmd *cmd)
{
	if (pre_check(args, k) == 1)
		return ;
	if (ft_is_builtin(args[*k]) == 0)
		cmd->is_builtin = 1;
	else
	{
		cmd->cmd_path = ft_find_pathcmd(*(cmd->env->env), args[*k]);
		if (cmd->cmd_path == NULL)
			cmd->cmd_flag = -1;
	}
	if (cmd->is_builtin == 1)
	{
		cmd->arg[(*i)++] = ft_strdup(args[*k]);
		cmd->cmd_flag = 1;
	}
	else if (cmd->cmd_path)
	{
		cmd->arg[(*i)++] = ft_strdup(args[*k]);
		cmd->cmd_flag = 1;
	}
}
