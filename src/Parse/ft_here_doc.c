/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:14:27 by rauferna          #+#    #+#             */
/*   Updated: 2024/04/24 12:25:38 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_here_doc_loop(int *fd, char *limit, char *line)
{
	pid_t pid;

	if (pipe(fd) == -1)
		exit(1);//exit
	pid = fork();
	if (pid == -1)
		exit(1);//exit
	else if (pid == 0)
	{
		write(2, "> ", 2);
		line = get_next_line(0);
		while (1)
		{
			if (ft_strncmp(line, limit, (ft_strlen(line) - 1)) == 0
				&& (ft_strlen(line) - 1) == ft_strlen(limit))
				break ;
			write(2, "> ", 2);
			write(fd[1], line, ft_strlen(line));
			line = get_next_line(0);
			if (!line)
				kill(pid, SIGTERM);
		}
	}
	waitpid(pid, NULL, 0);
}

void	ft_here_doc(char **args, int i, t_cmd *cmd)
{
	char		*line;
	char		*limit;
	int			fd[2];
	//si sales con Ctrl + D al salir no sale con Ctrl + D a la primera
	if (!args[i + 1] && ft_strlen(args[i]) <= 2)
	{
		error_syntax("newline");
		return ;
	}
	if (ft_strlen(args[i]) > 2)
		limit = args[i] + 2;
	else if (args[i + 1] && ft_strlen(args[i]) == 2)
		limit = args[i + 1];
	fd[1] = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_here_doc_loop(fd, limit, line);
	cmd->fds->infile = fd[1];
	close(fd[1]);
	unlink("temp");
}

/*
#include <termios.h>
#include <unistd.h>

void set_non_canonical_mode() {
    struct termios term;

    // get the current terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
*/
