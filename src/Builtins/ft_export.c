/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:12:54 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/02 13:15:21 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	ft_update_env(char ***env, int *size, char *variable)
{
	int	index;
	int	flag;

	if (ft_is_in_env_index(*env, variable, &index, &flag))
		return (ERROR);
	if (flag)
	{
		if (ft_strcontains(variable, '='))
		{
			free((*env)[index]);
			(*env)[index] = ft_strdup(variable);
			if (!(*env)[index])
				return (ERROR);
		}
	}
	else
	{
		*size += 1;
		*env = ft_realloc_doublep_char(*env, *size + 1);
		(*env)[(*size) - 1] = ft_strdup(variable);
		if (!(*env)[(*size) - 1])
			return (ERROR);
	}
	return (SUCCESS);
}

int	ft_export(t_cmd **cmd)
{
	int		i;
	char	**arg;

	arg = (*cmd)->arg;
	i = 1;
	if ((*cmd)->num_arg < 1)
		return (ft_print_sorted_env((*cmd)->env->env[0]));
	while (arg && arg[i])
	{
		if (ft_valid_name(arg[i]))
			return (ft_print_export_error(arg[i]));
		else
			if (ft_update_env((*cmd)->env->env, &((*cmd)->env->env_size),
				arg[i]))
				return (ERROR);
		i++;
	}
	return (SUCCESS);
}

/* int main(int argc, char **argv, char **env)
{
	t_cmd *cmd;
	char **dupe;

	dupe = ft_dpointer_dupe(env);
	cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	cmd->cmd_path = "/bin/ls";
	cmd->arg = (char **)malloc(sizeof(char *) * 4);
	cmd->arg[0] = "export";
	cmd->arg[1] = "A=B";
	cmd->arg[2] = "B=C";
	cmd->arg[3] = 0;
	cmd->env = (t_env *)malloc(sizeof(t_env) * 1);
	cmd->env->env_size = ft_dpointer_size(env);
	cmd->env->env = &dupe;
	cmd->num_arg = 0;
	ft_export(&cmd);
	ft_env(&cmd);
	return (0);
}  */