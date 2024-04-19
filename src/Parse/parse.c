/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:15:09 by rauferna          #+#    #+#             */
/*   Updated: 2024/04/19 14:27:40 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_fds(t_cmd *cmd)
{
	cmd->fds = ft_calloc(1, sizeof(t_fds));
	if (!cmd->fds)
	{
		ft_putstr_fd("Malloc Error\n", STDERR);
		return ;
	}
	if (cmd->outfile_flag == 0)
		cmd->fds->outfile = -1;
	if (cmd->infile_flag == 0)
		cmd->fds->infile = -1;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned int	lens1;
	unsigned int	lens2;
	unsigned int	n;

	i = 0;
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (lens1 > lens2)
		n = lens1;
	else
		n = lens2;
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]) && i < n)
		i++;
	if (i < n)
		return ((int)((unsigned char)(s1[i]) - ((unsigned char)s2[i])));
	else
		return (0);
}

static void	node_new(t_cmd *cmd, char **args)
{
	int	i;

	i = 0;
	cmd->infile_flag = 0;
	cmd->outfile_flag = 0;
	cmd->cmd_flag = 0;
	cmd->num_arg = 0;
	cmd->semicolon_flag = 0;
	cmd->is_builtin = 0;
	while (args[i])
		i++;
	cmd->arg = (char **)ft_calloc(i + 1, sizeof(char **));	//calcular long exacta
	if (!cmd->arg)
	{
		free (cmd->arg);
		return ;
	}
}

void	create_struct(char **args, t_data *data)
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
		node = ft_calloc(1, sizeof(t_cmd));
		if (!node)
			return ;
		node_new(node, args);
		node->next = NULL;
		node->arg = process_args(args, &i, node, data);
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

int	ft_parse(char *input, t_data *data)
{
	int		i;
	int		j;
	char	**args;
	//t_cmd	*current_node;
	t_cmd	*command;

	i = 0;
	j = 0;
	if (!input)
		return (ERROR);
	args = ft_split_mod(input, ' ');
	create_struct(args, data);
	if (data->cmd->infile_flag == 0 || data->cmd->outfile_flag == 0)//hcerlo en toda la estructura
		create_fds(data->cmd);
	ft_free_char(args);
	//checkear si cmd valid y si fd invalid
	//ft_printf("minishell: Todo mal\n");
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