/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:14:27 by rauferna          #+#    #+#             */
/*   Updated: 2024/06/25 21:10:49 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_check_double_greather(char **args, char *res, int i, t_cmd *cmd)
{
	if (ft_strlen(res) == 2)
		cmd->fds->outfile = ft_openfile(args[i + 1], 3);
	else
		cmd->fds->outfile = ft_openfile(res + 2, 3);
	if (ft_strlen(res) == 2)
		free(args[i + 1]);
	cmd->outfile_flag = 1;
}

static void	ft_here_doc_loop(char *line, char *limit, int fd)
{
	signal(SIGINT, SIG_DFL);
	write(2, "> ", 2);
	line = get_next_line(0);
	while (line)
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
	else
	{
		ft_putstr_fd("bash: warning: here-document delimited by ", 2);
		ft_putstr_fd("end-of-file (wanted `", 2);
		ft_putstr_fd(limit, 2);
		ft_putstr_fd("')\n", 2);
	}
}

static int	ft_here_doc_2(int fd[2], char *limit, char *line, t_data *data)
{
	int				status;
	pid_t			pid;
	struct termios	old_termios;
	struct termios	new_termios;

	tcgetattr(0, &old_termios);
	new_termios = old_termios;
	new_termios.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &new_termios);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		close(fd[0]);
		ft_here_doc_loop(line, limit, fd[1]);
		close(fd[1]);
		ft_free_all(data);
		exit(0);
	}
	tcsetattr(0, TCSANOW, &old_termios);
	ft_get_exit_code(pid, &status);
	return (0);
}

int	ft_here_doc(char *limit, t_cmd *cmd, t_data *data)
{
	char		*line;
	int			fd[2];

	line = NULL;
	if (!limit)
		return (1);
	if (pipe(fd) == -1)
		return (1);
	if (ft_here_doc_2(fd, limit, line, data) == 1)
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
