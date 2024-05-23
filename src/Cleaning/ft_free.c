/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:05:46 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/23 12:54:39 by ezhou            ###   ########.fr       */
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

void	ft_free_cmd_struct(t_cmd *cmd)
{
	t_cmd	*node;
	t_cmd	*next;

	node = cmd;
	if (!node)
		return ;
	while (node)
	{
		if (node->file_flag == 1)
			free(node->fds);
		//ft_printf("freed file\n");
		if (node->cmd_path)
			free(node->cmd_path);
		//ft_printf("freed path\n");
		if (node->arg)
			ft_free_char(node->arg);
		//ft_printf("freed arg\n");
		next = node->next;
		free(node);
		node = NULL;
		//ft_printf("*************************\n");
		node = next;
	}
}

void	ft_free_list(t_cmd *cmd)
{
	if (cmd)
		ft_free_cmd_struct(cmd);
}

int		ft_free_all(t_data *data)
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