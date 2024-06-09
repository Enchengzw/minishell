/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:14:27 by rauferna          #+#    #+#             */
/*   Updated: 2024/06/04 20:16:07 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		close(fd[0]);
		ft_here_doc_loop(line, limit, fd[1]);
		close(fd[1]);
		exit(0);
	}
	tcsetattr(0, TCSANOW, &old_termios);
	kill(pid, SIGTERM);
	waitpid(pid, NULL, 0);
	return (0);
}

static int	check_start(char **args, char *res, int i)
{
	if ((!args[i + 1] && ft_strlen(res) <= 2)
		|| ft_strncmp(args[i], "<<<", 3) == 0)
	{
		ft_error_syntax("newline");
		return (1);
	}
	return (0);
}

int	ft_here_doc(char **args, char *res, int i, t_cmd *cmd)
{
	char		*line;
	char		*limit;
	int			fd[2];

	if (check_start(args, res, i) == 1)
		return (1);
	line = NULL;
	if (ft_strlen(res) > 2)
		limit = res + 2;
	else if (args[i + 1] && ft_strlen(res) == 2)
		limit = args[i + 1];
	if (pipe(fd) == -1)
		return (1);
	if (ft_here_doc_2(fd, limit, line) == 1)
	{
		close(fd[0]);
		close(fd[1]);
		return (write(STDERR, "Here doc error\n", STDERR));
	}
	cmd->fds->infile = fd[0];
	cmd->infile_flag = 1;
	close(fd[1]);
	return (0);
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
