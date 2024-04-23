/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:14:27 by rauferna          #+#    #+#             */
/*   Updated: 2024/04/23 11:54:15 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <termios.h>

static void	ft_here_doc_loop(char *line, char *limit, int fd)
{
	write(2, "> ", 2);
	line = get_next_line(0);
	while (1)
	{
		if (ft_strncmp(line, limit, (ft_strlen(line) - 1)) == 0
			&& (ft_strlen(line) - 1) == ft_strlen(limit))
			break ;
		write(2, "> ", 2);
		write(fd, line, ft_strlen(line));
		if (line)
			free(line);
		line = get_next_line(0);
	}
	if (line)
		free(line);
}

static int	ft_here_doc_2(int *fd, char *limit, char *line)
{
	pid_t			pid;
	struct termios	old_termios;
	struct termios	new_termios;

	tcgetattr(0, &old_termios);
	new_termios = old_termios;
	new_termios.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &new_termios);
	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		ft_here_doc_loop(line, limit, fd[1]);
		exit(0);
	}
	tcsetattr(0, TCSANOW, &old_termios);
	waitpid(pid, NULL, 0);
	return (0);
}

int	ft_here_doc(char **args, int i, t_cmd *cmd)
{
	char		*line;
	char		*limit;
	int			fd[2];
	//si sales con Ctrl + D al salir no sale con Ctrl + D a la primera
	if (!args[i + 1] && ft_strlen(args[i]) <= 2)
	{
		error_syntax("newline");
		return (1);
	}
	if (ft_strlen(args[i]) > 2)
		limit = args[i] + 2;
	else if (args[i + 1] && ft_strlen(args[i]) == 2)
		limit = args[i + 1];
	fd[1] = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ft_here_doc_2(fd, limit, line) == 1)
		return (1);
	cmd->fds->infile = fd[1];
	close(fd[1]);
	unlink("temp");
	return (0);
}

/*
#include <termios.h>
#include <unistd.h>

void set_non_canonical_mode()
{
    struct termios term;

    // get the current terminal settings
    tcgetattr(STDIN_FILENO, &term);

    // modify the settings to non-canonical mode
    term.c_lflag &= ~(ICANON | ECHO);

    // set the terminal to non-canonical mode
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
*/
