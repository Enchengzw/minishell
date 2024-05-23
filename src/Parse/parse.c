/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:15:09 by rauferna          #+#    #+#             */
/*   Updated: 2024/05/23 13:04:40 by ezhou            ###   ########.fr       */
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

static	t_cmd	*node_new(t_cmd *cmd, char **args, t_data *data, int quote, int *j)
{
	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->file_flag = 0;
	cmd->infile_flag = 0;
	cmd->outfile_flag = 0;
	cmd->cmd_flag = 0;
	cmd->num_arg = 0;
	cmd->semicolon_flag = 0;
	cmd->is_builtin = 0;
	cmd->quote = quote;
	cmd->env = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!cmd->env)
		return (NULL);
	cmd->env->env = &(data->env);
	cmd->env->env_size = ft_dpointer_size(data->env);
	cmd->arg = ft_split_mod(args[*j], ' ');
	if (!cmd->arg)
		return (free(cmd->arg), NULL);
	cmd->exit_code = &(data->exit_code);
	return (cmd);
}

void	ft_create_struct(char **args, t_data *data, int quote)
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
		node = node_new(node, args, data, quote, &i);
		if (!node)
			return ;
		node->next = NULL;
		node->arg = ft_process_args(node, data);
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

static int	ft_check_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (str[i + 1] == '\0')
				return (1);
			if (str[i + 1] == '|' && str[i + 2] == '|')
				return (1);
			if (str[i + 1] == ';' && str[i + 2] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

//mirar : (es un comodín)
int	ft_parse(char *input, t_data *data)
{
	int		quote;
	char	**args;

	quote = 0;
	if (!input)
		return (ERROR);
	input = ft_pre_check_quotes(input, &quote);
	if (!input)
		return (write(2, "Unspected quote \n", 17), STDERR);
	if (ft_check_pipes(input) == 1)
		return (error_syntax("|"));
	args = ft_split_mod_pipe(input, '|', 1);//revisar comillas
	ft_create_struct(args, data, quote);
	if (data->cmd)
		link_nodes(data);
	free(input);
	ft_free_char(args);
	return (SUCCESS);
}

/*
    current_node = data->cmd;
    while (current_node)
    {
        int k = 0;
        while (current_node->arg[k])
            ft_printf("%s\n", current_node->arg[k++]);
        current_node = current_node->next;
        ft_printf("--------\n");
    }
		cmd->fds->infile = open(args[*i], O_RDONLY, 0644);
 && (i == 0 || (ft_strncmp(args[i - 1], "|", 1) == 0)
 && ft_strlen(args[i - 1]) == 1)

 	if (ft_strcmp(command, "echo $USER"))
	{
		execve("/usr/bin/whoami", &"whoami" ,data->env);
		exit(0);
	}
	int check_spaces(char *str)
	{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else
			return (1);
	}
	return (0);
}
void	ft_init_message(void)
{
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(YELLOW_TEXT "             ____WELCOME TO MINISHELL____\n", 1);
	ft_putstr_fd(YELLOW_TEXT "				Made by ezhou and rauferna\n", 1);
	ft_putstr_fd("\n", 1);
}
!!CURIOSO Caso= :

1º arg = <infile or command
2º arg = command or -X or <<here_doc or file
3º arg = >> or > or -X or...
|
1º arg = <infile or command
2º arg = command or -X or <<here_doc or file
3º arg = >> or > or -X or...
execve 1º ruta 2º argumento spliteado 3º env
//considerar añadir j para no guardar los valores invalidos, que hacer con valores invalidos
//si pongo cat test.c 232432 imprime test.c y error pero si hago cat test.c | 232432 solo muestra error
//args = ft_split_mod(*args, '|'); s[i] == ';' || s[i] == '|'  && s[i + 1] != 'n'
*/