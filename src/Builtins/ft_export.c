/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:12:54 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/27 12:44:03 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static char	*ft_concatenate(char *label, char *value, char *old_variable)
{
	char	*aux;
	char	*new_value;
	char	*new_label;
	char	*result;

	aux = ft_get_value(old_variable);
	if (!aux)
		return (NULL);
	new_value = ft_strjoin(aux, value);
	if (!new_value)
		return (free(aux), NULL);
	new_label = ft_strtrim(label, "+");
	if (!new_label)
		return (free(aux), free(new_value), NULL);
	result = ft_make_export_line(new_label, new_value);
	if (!result)
		return (free(aux), free(new_value), free(new_label), NULL);
	free(aux);
	free(new_value);
	free(new_label);
	return (result);
}

static int	ft_update_old(char *variable, char ***env, int index)
{
	char	*label;
	char	*value;
	char	*temp;

	if (!ft_strcontains(variable, '='))
		return (SUCCESS);
	label = ft_get_label(variable);
	value = ft_get_value(variable);
	if (!label || !value)
		return (free(label), free(value), ERROR);
	if (ft_strcontains(label, '+'))
		temp = ft_concatenate(label, value, (*env)[index]);
	else
		temp = ft_make_export_line(label, value);
	if (!temp)
		return (free(label), free(value), ERROR);
	free((*env)[index]);
	(*env)[index] = temp;
	free(label);
	free(value);
	return (SUCCESS);
}

static int	ft_add_new(char *variable, int size, char ***env)
{
	char	*label;
	char	*value;

	label = ft_get_label(variable);
	if (!label)
		return (ERROR);
	if (ft_strcontains(variable, '='))
	{
		value = ft_get_value(variable);
	}
	else
		value = ft_strdup("");
	if (!value)
		return (free(label), ERROR);
	(*env)[(size) - 1] = ft_make_export_line(label, value);
	if (!(*env)[(size) - 1])
		return (free(label), free(value), ERROR);
	free(label);
	free(value);
	return (SUCCESS);
}

static int	ft_update_env(char ***env, int *size, char *variable)
{
	int	index;
	int	flag;

	if (ft_is_in_env_index(*env, variable, &index, &flag))
		return (ERROR);
	if (flag)
	{
		if (ft_update_old(variable, env, index))
			return (ERROR);
	}
	else
	{
		*size += 1;
		*env = ft_realloc_doublep_char(*env, *size + 1);
		if (!env || ft_add_new(variable, *size, env))
			return (ERROR);
	}
	return (SUCCESS);
}

int	ft_export(t_cmd **cmd)
{
	int		i;
	char	**arg;

	arg = (*cmd)->arg;
	(*cmd)->num_arg = ft_dpointer_size(arg);
	i = 0;
	if ((*cmd)->num_arg == 1)
		return (ft_print_sorted_env((*cmd)->env->env[0]));
	while (arg && arg[++i])
	{
		if (ft_valid_name(arg[i]))
			return (ft_print_export_error(arg[i]));
		else
			if (ft_update_env((*cmd)->env->env, &((*cmd)->env->env_size),
					arg[i]))
				return (ft_printf("Malloc Error\n"), ERROR);
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