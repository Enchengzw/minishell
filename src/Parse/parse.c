/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:15:09 by rauferna          #+#    #+#             */
/*   Updated: 2024/04/12 14:00:31 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char	*find_path_loop(char *path_line, char *path, char *command)
{
	int		i;
	char	**paths;

	i = 0;
	while (path_line[i])
	{
		paths = ft_split(path_line, ':');
		if (!paths || !paths[i])
			break ;
		path = paths[i];
		if (ft_strchr(command, '/') == NULL)
		{
			path = ft_strjoin(path, "/");
			path = ft_strjoin(path, command);
		}
		else
			path = ft_strjoin(path, ft_strrchr(command, '/'));
		if (access(path, F_OK) == 0)
			return (free(paths), path);
		i++;
	}
	error_cnf(command);
	return (free(path), NULL);
}

char	*find_pathcmd(char **envp, char *command)
{
	int		i;
	char	*path;
	char	*path_line;
	char	*res;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	path_line = envp[i] + 5;
	return (find_path_loop(path_line, path, command));
}

int	openfile(char *file, int type)
{
	int	fd[2];

	if (type == 1)
	{
		fd[0] = open(file, O_RDONLY, 0644);
		if (fd[0] == -1)
			error_fnf(file);
		return (fd[0]);
	}
	else if (type == 2)
	{
		fd[1] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[1] == -1)
			error_fnf(file);
		return (fd[1]);
	}
	else if (type == 3)
	{
		fd[1] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd[1] == -1)
			error_fnf(file);
		return (fd[1]);
	}
	exit(EXIT_FAILURE);
}

t_cmd	*ft_parse(char *input, t_data *data)
{
	t_cmd	*command;

	if (!input)
		return (NULL);
	command = parseinit(input, data);
	//ft_printf("minishell: Todo mal\n");
	return (command);
}

/*
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