/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:05:46 by ezhou             #+#    #+#             */
/*   Updated: 2024/06/25 19:09:59 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h> 

/* typedef struct s_data
{
	// t_token		*token;
	char			*user_input;
	char			**env;
	t_cmd			*cmd;
	int				std_in;
	int				std_out;
}					t_data;

typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*previous;
	t_fds           *fds;
	char			*cmd_path;
	char			**arg;
	t_env			*env;
	int				num_arg;
}					t_cmd; */

void	ft_format_exit_code(int *exit_code)
{
	if (*exit_code > 255)
		*exit_code = *exit_code % 255;
}

void	ft_continue_free_cmd(t_cmd *cmd)
{
	if (cmd->arg)
	{
		ft_free_char(cmd->arg);
		cmd->arg = NULL;
	}
	if (cmd->type)
	{
		free(cmd->type);
		cmd->type = NULL;
	}
	if (cmd->env)
	{
		if (cmd->env)
			free(cmd->env);
		cmd->env = NULL;
	}
}

void	ft_free_cmd_struct(t_cmd *cmd)
{
	t_cmd	*node;
	t_cmd	*next;

	node = cmd;
	if (!node)
		return ;
	while (node)
	{
		if (node->file_flag != 0 && node->file_flag != -2)
		{
			ft_close(&(node->fds->infile));
			ft_close(&(node->fds->outfile));
			free(node->fds);
			node->fds = NULL;
		}
		if (node->cmd_path)
			free(node->cmd_path);
		ft_continue_free_cmd(node);
		next = node->next;
		free(node);
		node = NULL;
		node = next;
	}
}

void	ft_free_list(t_cmd *cmd)
{
	if (cmd)
		ft_free_cmd_struct(cmd);
}

int	ft_free_all(t_data *data)
{
	if (data->user_input)
		free(data->user_input);
	ft_free_list(data->cmd);
	ft_free_char(data->env);
	if (ft_close(&(data->std_in)))
		return (ft_printf("Close failure\n"), ERROR);
	if (ft_close(&(data->std_out)))
		return (ft_printf("Close failure\n"), ERROR);
	free(data);
	return (SUCCESS);
}
