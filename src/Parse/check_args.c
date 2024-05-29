/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:54:54 by rauferna          #+#    #+#             */
/*   Updated: 2024/05/23 13:03:39 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	check_cmd(char **args, int *i, int *k, t_cmd *cmd)
{
	if (*k > 0 && (args[*k - 1][0] == '<' && !args[*k - 1][1])
		&& (args[*k - 1][0] == '<' && args[*k - 1][1] == '<'))
		return ;
	else
	{
		if (ft_is_builtin(args[*k]) == 0)
			cmd->is_builtin = 1;
		else
		{
			cmd->cmd_path = ft_find_pathcmd(*(cmd->env->env), args[*k]);
			if (!cmd->cmd_path)
				cmd->cmd_flag = -1;
		}
	}
	if (cmd->is_builtin == 1)
	{
		cmd->arg[(*i)++] = ft_strdup(args[*k]);
		cmd->cmd_flag = 1;
	}
	else if (cmd->cmd_path)
	{
		cmd->arg[(*i)++] = ft_strdup(args[*k]);
		cmd->cmd_flag = 1;
	}
}

static void	ft_check_script_or_program(char **args, int *k, int *i, t_cmd *cmd)
{
	if (access(args[*k], F_OK | R_OK) != 0)
	{
		error_fnf(args[*k]);
		cmd->file_flag = -1;
		return ;
	}
	cmd->cmd_path = ft_strdup(args[*k]);
	cmd->arg[(*i)++] = ft_strdup(args[*k]);
	cmd->cmd_flag = 1;
}

static void	ft_check_rest(char **args, int *i, int *k, t_cmd *cmd)
{
	int	start;

	start = 0;
	if (ft_strncmp(args[*k], "./", 2) == 0)
		ft_check_script_or_program(args, k, i, cmd);
	else if (cmd->cmd_flag == 0)
		check_cmd(args, i, k, cmd);
	else if (cmd->cmd_flag == 1)
	{
		while (args[*k] && args[*k][start] == ' ')
			start++;
		if ((*k > 0 && args[*k - 1][0] == '>') || args[*k - 1][0] == '<')
			return ;
		else
			cmd->arg[(*i)++] = ft_copy_char(args[*k], cmd);
	}
	else
		error_syntax(args[*k]);
}

char	**ft_process_args(t_cmd *cmd, t_data *data, char **args)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (cmd->arg[k] == NULL)
	{
		if (args[k + 1] != NULL)
			error_syntax("|");
		cmd->cmd_flag = -1;
	}
	while (cmd->arg[k])
	{
		if (cmd->cmd_flag == -1 || cmd->file_flag == -1)
			break ;
		if (cmd->arg[k][0] == '<' || cmd->arg[k][0] == '>')
			cmd->file_flag = ft_check_redirections(cmd->arg, k, cmd, data);
		else
			ft_check_rest(cmd->arg, &i, &k, cmd);
		if (cmd->arg[k] != NULL)
			k++;
	}
	cmd->arg[i] = NULL;
	return (cmd->arg);
}

/*
		if (args[*j][0] == '|' && !args[*j][1])
			break ;
while ((*(cmd->env->env))[k])
//args[*j][0] == '$' ft_strchr(args[*j], '$') == NULL
		{
			if (ft_strncmp((*(cmd->env->env))[k], args[*j] + start + 1,
				ft_strlen_nospace(args[*j] + start) - 1) == 0)
				cmd->arg[(*i)++] = ft_strdup((*(cmd->env->env))[k]
						+ ft_strlen_nospace(args[*j] + start)); 
			k++;
		}
		while ((*(cmd->env->env))[k])
		{
			char *equal_sign = ft_strchr((*(cmd->env->env))[k], '=');
			if (equal_sign != NULL)
			{
				int name_length = equal_sign - (*(cmd->env->env))[k];
				if (ft_strncmp((*(cmd->env->env))[k], args[*j] + start + 1, name_length) == 0)
					cmd->arg[(*i)++] = ft_strdup(equal_sign + 1);
			}
			k++;
		}
	int k = 0;
	while (node->cmd)
	{
		while (node->cmd->arg[k])
			ft_printf("%s\n", node->cmd->arg[k++]);
		node->cmd = node->cmd->next;
		ft_printf("--------\n");
	}
	size_t ft_strlen_nospace(char *str)
{
	size_t i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
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

	if (cmd->is_builtin == 1)
	{
		if (ft_strcmp("echo", args[0]) == 0
			&& ft_strcmp("-n", args[1]) == 0)
			cmd->arg[(*i)++] = ft_strdup(args[*j]);
		else if (args[*i][0] != '-')
			cmd->arg[(*i)++] = ft_strdup(args[*j]);
		else
		{
			error_syntax(args[*j]);
			cmd->cmd_flag = -1;
		}
	}
*/