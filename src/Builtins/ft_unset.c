/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:30:18 by ezhou             #+#    #+#             */
/*   Updated: 2024/03/22 15:35:30 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_update_env(char ***env, int size, int index)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_calloc(size, sizeof(char *));
	while (env && *env && (*env)[i])
	{
		if (i != index)
		{
			new[j] = ft_strdup((*env)[i]);
			j++;
		}
		i++;
	}
	ft_free_char(*(env));
	*env = new;
	return (SUCCESS);
}

int	ft_unset(t_cmd **cmd)
{
	int		i;
	char	**arg;
	int		index;

	arg = (*cmd)->arg;
	i = 0;
	if ((*cmd)->num_arg < 1)
		return (SUCCESS);
	while (arg[++i])
	{
		if (ft_valid_name(arg[i]))
			return (ft_print_export_error(arg[i]));
		else
		{
			if (ft_is_in_env_index((*cmd)->env->env, arg[i], &index))
			{
				ft_update_env(&((*cmd)->env->env), (*cmd)->env->env_size,
					index);
				(*cmd)->env->env_size -= 1;
			}
			else
				return (SUCCESS);
		}
	}
	return (SUCCESS);
}

/* int	main(int argc, char **argv, char **env)
{
	t_cmd *cmd;
	int i = 0;

	cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	cmd->cmd_path = "/bin/ls";
	cmd->arg = (char **)malloc(sizeof(char *) * 4);
	cmd->arg[0] = "unset";
	cmd->arg[1] = "PWD";
	cmd->arg[2] = 0;
	cmd->arg[3] = 0;
	cmd->env = (t_env *)malloc(sizeof(t_env) * 1);
	cmd->env->env_size = ft_dpointer_size(env);
	cmd->env->env = ft_dpointer_dupe(env);
	cmd->num_arg = 2;
	ft_unset(&cmd);
	ft_env(&cmd);
	return (0);
} */