/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:54:54 by rauferna          #+#    #+#             */
/*   Updated: 2024/04/22 11:46:10 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	check_cmd1(char **env, char **args, int *j, t_cmd *cmd)
{
	if (*j > 0 && args[*j - 1][0] == '<' && !args[*j - 1][1])
		return ;
	else
	{
		if (ft_is_builtin(args[*j]) == 0)
			cmd->is_builtin = 1;
		else
		{
			cmd->cmd_path = find_pathcmd(env, args[*j]);
			if (!cmd->cmd_path)
				cmd->cmd_flag = -1;
		}
	}
}

static void	check_cmd2(char **args, int *i, int *j, t_cmd *cmd)
{
	if (cmd->cmd_path)
	{
		cmd->arg[(*i)++] = ft_strdup(args[*j]);
		cmd->cmd_flag = 1;
	}
}

static void	ft_check_exceptions(char **args, int *j, t_cmd *cmd)
{
	if (args[*j] && (args[*j][0] == '|' || args[*j][0] == ';')
		&& (!args[*j + 1] || !args[*j + 1][0]))
		error_syntax(args[*j]);
	if (args[*j] && args[*j][0] == ';')
		cmd->semicolon_flag = 1;
}

char	**process_args(char **args, int *j, t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (args[*j] && args[*j][0] != '|' && args[*j][0] != ';')
	{
		if (cmd->cmd_flag == -1 || cmd->file_flag == -1)
			break ;
		if (args[*j][0] == '<' || args[*j][0] == '>')
			cmd->file_flag = check_redirections(args, *j, cmd);
		else if (ft_strncmp(args[*j], "./", 2) == 0)
			cmd->arg[(i)++] = ft_strdup(args[*j]);
		else if (cmd->cmd_flag == 0)
		{
			check_cmd1(data->env, args, j, cmd);
			check_cmd2(args, &i, j, cmd);
		}
		else if (cmd->cmd_flag == 1)
			cmd->arg[(i)++] = ft_strdup(args[*j]);
		else
			error_syntax(args[*j]);
		(*j)++;
	}
	ft_check_exceptions(args, j, cmd);
	return (cmd->arg);
}

/*
	int k = 0;
	while (node->cmd)
	{
		while (node->cmd->arg[k])
			ft_printf("%s\n", node->cmd->arg[k++]);
		node->cmd = node->cmd->next;
		ft_printf("--------\n");
	}
void	check_args(char **args, t_data *data)
{
	int		i;
	int		j;
	t_data	*temp;

	i = 0;
	j = 0;
	temp = data;
	temp->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!temp)
		return ;
	temp->cmd->next = NULL;
	while (args && args[j])
	{
		while (args[i++])
		temp->cmd->arg = (char **)ft_calloc(i + 1, sizeof(char **));//calcular long exacta
		if (!temp->cmd->arg)
		{
			free (temp->cmd->arg);
			return ;
		}
		i = 0;
		data->cmd = temp->cmd;
		if (args[j])
		{
			j++;
			temp->cmd->next = ft_calloc(1, sizeof(t_cmd));
			if (!temp->cmd->next)
				return ;
			temp->cmd = temp->cmd->next;
		}
	}
}
*/
/*
		if (data->cmd->file_flag == 1)
		{
			int k = 0;
			t_cmd *temp_cmd;
			temp_cmd = data->cmd->previous;
			while (temp_cmd->arg[k])
				ft_printf("%s\n", temp_cmd->arg[k++]);
			ft_printf("--------\n");
		}
	(*i)++;
	cmd->arg[*i] = NULL;

	int	i;
	int	j;

	i = 0;
	j = 0;
	data->cmd->file_flag = 0;
	while (data->cmd)
	{
		data->cmd->cmd_flag = 0;
		process_args(args, &j, &i, data);
		if (args[j])
			j++;
		data->cmd->num_arg = j - data->cmd->file_flag;
		data->cmd = data->cmd->next;
	}
void	check_args(char **args, char *command, t_data *data)
{
    int	i;
    int	j;

    i = 0;
    j = 0;
    data->cmd->file_flag = 0;
    while (args && args[j])
    {
        data->cmd = ft_calloc(1, sizeof(t_data));
        if (!data->cmd)
            return ;
        data->cmd->arg = (char **)ft_calloc(10000, sizeof(char *));
        if (!data->cmd->arg)
            return ;
        args = ft_split_mod(command, ' ');
        while (args[i])
        {
            data->cmd->arg = (char **)realloc(data->cmd->arg, (i + 1) * sizeof(char *));
            if (!data->cmd->arg)
            {
                free(args);
                return ;
            }
            data->cmd->arg[i] = args[i];
            i++;
        }
        data->cmd->cmd_flag = 0;
        i = 0;
        process_args(args, &j, &i, data);
        if (args[j])
            j++;
        data->cmd->num_arg = i;
        data->cmd = data->cmd->next;
        if (data->cmd == NULL)
            break ;
    }
}

t_cmd	*parseinit(char *command, t_data *data)
{
	int		i;
	int		j;
	char	**args;

	i = 0;
	j = 0;
	if (!command)
		return (NULL);
	args = ft_split_mod(command, ' ');
	check_args(args, command, data);
	return (data->cmd);
}

    		int k = 0;
		while (data->cmd->arg[k])
		{
			ft_printf("%s", data->cmd->arg[k++]);
		}

for each command in the command line:
    if the command includes a pipe:
        split the command into two parts at the pipe
        execute the first part and store its output
        pass the output as input to the second part and execute it
    else:
        execute the command
*/