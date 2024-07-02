/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:15:09 by rauferna          #+#    #+#             */
/*   Updated: 2024/07/02 19:30:40 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	link_nodes(t_data *data)
{
	t_cmd	*cmd;
	t_cmd	*next;

	cmd = data->cmd;
	cmd->previous = NULL;
	next = data->cmd->next;
	while (next)
	{
		next->previous = cmd;
		cmd = cmd->next;
		next = next->next;
	}
}

static	t_cmd	*node_new(t_cmd *cmd, char **args, t_data *data, int *j)
{
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->file_flag = 0;
	cmd->infile_flag = 0;
	cmd->outfile_flag = 0;
	cmd->cmd_flag = 0;
	cmd->num_arg = 0;
	cmd->is_builtin = 0;
	cmd->two_points = 0;
	cmd->num_i = 0;
	cmd->env = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!cmd->env)
		return (NULL);
	cmd->env->env = &(data->env);
	cmd->env->env_size = ft_dpointer_size(data->env);
	cmd->type = ft_calloc(ft_len_type(args[*j]) + 1, sizeof(char));
	if (!cmd->type)
		return (ft_putstr_fd("Error: Malloc failed\n", 2), NULL);
	cmd->arg = ft_split_mod(args[*j], cmd);
	if (!cmd->arg)
		return (ft_putstr_fd("Error: Split failed\n", 2), free(cmd->arg), NULL);
	cmd->exit_code = &(data->exit_code);
	return (cmd);
}

void	ft_create_struct(char **args, t_data *data)
{
	int		i;
	t_cmd	*node;
	t_cmd	*last;

	if (!data)
		return ;
	i = 0;
	last = NULL;
	while (args[i])
	{
		node = node_new(node, args, data, &i);
		if (!node)
			return ;
		node->next = NULL;
		ft_process_args(node, data, args);
		if (args[i])
			i++;
		if (last)
			last->next = node;
		else
			data->cmd = node;
		last = node;
		node->num_arg = i;
	}
}

static int	ft_check_syntax_error(char *str)
{
	int	i;

	if (str[0] == '|' || str[0] == ';' || str[0] == '&')
		return (ft_error_syntax(str));
	i = 0;
	while (str[i])
	{
		if (str[i] == '|' || str[i] == ';' || str[i] == '&')
		{
			if (str[i] == '&' && str[i + 1] == '\0')
				return (ft_error_syntax("&"));
			if (str[i] == ';' && str[i + 1] == '\0')
				return (ft_error_syntax(";"));
			if (str[i] == '|' && str[i + 1] == '\0')
				return (ft_error_syntax("|"));
			if (str[i + 1] == '|')
				return (ft_error_syntax("|"));
			if (str[i + 1] == ';')
				return (ft_error_syntax(";"));
		}
		i++;
	}
	return (0);
}

int	ft_parse(char *input, t_data *data)
{
	int		quote;
	char	**args;

	data->is_interrupted = 0;
	quote = 0;
	if (!input)
		return (ERROR);
	input = ft_pre_check_quotes(input, &quote);
	if (!input)
	{
		free(input);
		return (write(2, "Unspected quote \n", 17), STDERR);
	}
	if (ft_check_syntax_error(input) == 1)
	{
		free(input);
		return (STDERR);
	}
	args = ft_split_mod_pipe(input);
	ft_create_struct(args, data);
	if (data->cmd)
		link_nodes(data);
	free(input);
	ft_free_char(args);
	return (SUCCESS);
}
