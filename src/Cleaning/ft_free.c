/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:05:46 by ezhou             #+#    #+#             */
/*   Updated: 2024/04/23 11:46:23 by rauferna         ###   ########.fr       */
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

void	ft_free_list(t_cmd *cmd)
{
	t_cmd *node;

	node = cmd;
	while (cmd)
	{
		if (node->fds)
			free(node->fds);
		ft_free_char(node->arg);
		free(cmd);
		cmd = cmd->next;
	}
}

void	ft_free_content(t_data *data)
{
	if (data->user_input)
		free(data->user_input);
	//if (data->cmd)
		//ft_free_list(data->cmd);
}

