/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:30:18 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/02 16:02:47 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	ft_update_env(char ***env, int size, int index)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_calloc(size, sizeof(char *));
	if (!new)
		return (ft_putstr_fd("Malloc Error\n", 2), ERROR);
	while (env && *env && (*env)[i])
	{
		if (i != index)
		{
			new[j] = ft_strdup((*env)[i]);
			if (!new[j])
				return (ft_free_char(new), ft_putstr_fd("Malloc Error\n", 2), ERROR);
			j++;
		}
		i++;
	}
	ft_free_char(*(env));
	*env = new;
	return (SUCCESS);
}

int	ft_unset_loop(t_cmd **cmd, char *arg, int *index)
{
	int flag;

	flag = 0;
	if (ft_valid_name(arg))
			ft_print_export_error(arg);
	else
	{
		if (ft_is_in_env_index((*cmd)->env->env[0], arg, index, &flag))
			return (ERROR);
		if (flag)
		{
			if (ft_update_env((*cmd)->env->env, (*cmd)->env->env_size,
				*index))
				return (ERROR);
			(*cmd)->env->env_size -= 1;
		}
	}
	return (SUCCESS);
}

int	ft_unset(t_cmd **cmd)
{
	int		i;
	char	**arg;
	int		index;

	(*cmd)->num_arg = ft_dpointer_size((*cmd)->arg);
	arg = (*cmd)->arg;
	i = 0;
	if ((*cmd)->num_arg < 1)
		return (SUCCESS);
	while (arg[++i])
	{
		if (ft_unset_loop(cmd, arg[i], &index))
			return (ERROR);
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
	cmd->arg[0] = "unset";
	cmd->arg[1] = "A";
	cmd->arg[2] = "B";
	cmd->arg[3] = 0;
	cmd->env = (t_env *)malloc(sizeof(t_env) * 1);
	cmd->env->env_size = ft_dpointer_size(env);
	cmd->env->env = &dupe;
	cmd->num_arg = 2;
	ft_export(&cmd);
	ft_env(&cmd);
	ft_unset(&cmd);
	ft_env(&cmd);
	return (0);
}  */