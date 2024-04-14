/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:54:54 by rauferna          #+#    #+#             */
/*   Updated: 2024/04/12 13:57:45 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_cmd(char **args, int *i, int *j, t_cmd *cmd, t_data *data)
{
	if (*j > 0 && args[*j - 1][0] == '<')
		return ;	
	if (cmd->cmd_flag == 1)
		check_redirections(args, *j, cmd);
	else
	{
		cmd->cmd_path = find_pathcmd(data->env, args[*j]);
		if (cmd->cmd_path)
		{
			cmd->cmd_flag = 1;
			cmd->arg[(*i)++] = args[*j];
		}
	}
}

void	process_args(char **args, int *j, int *i, t_cmd *cmd, t_data *data)
{
	cmd->num_arg = 0;
	while (args[*j] && args[*j][0] != '|' && args[*j][0] != ';')
	{
		if (args[*j][0] == '<' || args[*j][0] == '>')
			check_redirections(args, *j, cmd);
		else if (ft_strncmp(args[*j], "./", 2) == 0)
			cmd->arg[(*i)++] = args[*j];
		else if (args[*j][0] != '-')
			check_cmd(args, i, j, cmd, data);
		else if (args[*j][0] == '-' && args[*j][1] && cmd->cmd_flag == 1)
			cmd->arg[(*i)++] = args[*j];
		else
			error_syntax(args[*j]);
		(*j)++;
	}
	if (args[*j] && (args[*j][0] == '|' || args[*j][0] == ';')
		&& (!args[*j + 1] || !args[*j + 1][0]))
		error_syntax(args[*j]);
}

void	check_args(char **args, char *command, t_data *data)
{
	int		i;
	int		j;
	t_cmd	*temp;

	i = 0;
	j = 0;
	data->cmd->file_flag = 0;
	temp = data->cmd;
	temp = ft_calloc(1, sizeof(t_cmd));
	if (!temp)
		return ;
	temp->next = NULL;
	while (args && args[j])
	{
		while (args[i])
			i++;
		temp->arg = (char **)ft_calloc(i + 1, sizeof(char **));
		if (!temp->arg)
		{
			free (temp->arg);
			return ;
		}
		temp->cmd_flag = 0;
		i = 0;
		process_args(args, &j, &i, temp, data);
		if (args[j])
			j++;
		temp->num_arg = i;
		if (temp->next)
			temp = temp->next;
		else if (args[j])
		{
			temp->next = ft_calloc(1, sizeof(t_cmd));
			if (!temp->next)
				return ;
			temp = temp->next;
			temp->next = NULL;
		}
		data->cmd = temp;
	}
	data->cmd->next = NULL;
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
	int k = 0;
	while (data->cmd)
	{
		while (data->cmd->arg[k])
			ft_printf("%s\n", data->cmd->arg[k++]);
		data->cmd = data->cmd->next;
	}
	return (data->cmd);
}

/*
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