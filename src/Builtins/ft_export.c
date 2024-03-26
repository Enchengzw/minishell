/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:12:54 by ezhou             #+#    #+#             */
/*   Updated: 2024/03/22 16:34:52 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_update_env(char ***env, int *size, char *variable)
{
	int	index;

	if (ft_is_in_env_index(*env, variable, &index))
	{
		if (ft_strcontains(variable, '='))
		{
			free((*env)[index]);
			(*env)[index] = ft_strdup(variable);
		}
	}
	else
	{
		*size += 1;
		*env = ft_realloc_doublep_char(*env, *size + 1);
		(*env)[(*size) - 1] = ft_strdup(variable);
	}
}

int	ft_export(t_cmd **cmd)
{
	int		i;
	char	**arg;

	arg = (*cmd)->arg;
	i = 1;
	if ((*cmd)->num_arg < 1)
		return (ft_print_sorted_env((*cmd)->env->env));
	while (arg && arg[i])
	{
		if (ft_valid_name(arg[i]))
			return (ft_print_export_error(arg[i]));
		else
			ft_update_env(&((*cmd)->env->env), &((*cmd)->env->env_size),
				arg[i]);
		i++;
	}
	return (SUCCESS);
}

/* int main(int argc, char **argv, char **env)
{
	t_cmd *cmd;
	int	i = 0;

	cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	cmd->cmd_path = "/bin/ls";
	cmd->arg = (char **)malloc(sizeof(char *) * 4);
	cmd->arg[0] = "export";
	cmd->arg[1] = "a=aisjdhdai";
	cmd->arg[2] = "b=gkjshdkf";
	cmd->arg[3] = 0;
	cmd->env = (t_env *)malloc(sizeof(t_env) * 1);
	cmd->env->env_size = ft_dpointer_size(NULL);
	cmd->env->env = ft_dpointer_dupe(NULL);
	cmd->num_arg = 2;
	ft_export(&cmd);
	printf("%s\n", (cmd->env->env)[102]);
	printf("%s\n", (cmd->env->env)[103]);
	ft_env(&cmd);
	return (0);
}  */