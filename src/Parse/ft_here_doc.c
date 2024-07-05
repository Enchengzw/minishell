/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:14:27 by rauferna          #+#    #+#             */
/*   Updated: 2024/07/02 20:37:08 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//SIGINT Cntr + C
//SIGQUIT Cntr + '\'

static int	check_start(char **args, char *res, int *i, t_cmd *cmd)
{
	if ((!args[*i + 1] && ft_strlen(res) <= 2)
		|| ft_strncmp(args[*i], "<<<", 3) == 0)
	{
		ft_error_syntax("newline");
		ft_free_redirection_space(cmd->arg[*i], &(cmd->arg[*i + 1]), i);
		return (1);
	}
	return (0);
}

char	*ft_here_doc_check(char *res, int *i, t_cmd *cmd)
{
	char	*limit;

	if (check_start(cmd->arg, res, i, cmd) == 1)
		return (NULL);
	if (ft_strlen(res) > 2)
		limit = res + 2;
	else if (cmd->arg[*i + 1] && ft_strlen(res) == 2)
		limit = cmd->arg[*i + 1];
	return (limit);
}

void	ft_check_double_greather(char **args, char *res, int i, t_cmd *cmd)
{
	if (ft_strlen(res) == 2)
		cmd->fds->outfile = ft_openfile(args[i + 1], 3);
	else
		cmd->fds->outfile = ft_openfile(res + 2, 3);
	cmd->outfile_flag = 1;
}

static void	ft_here_doc_loop(char *limit, int fd)
{
	char	*line;

	line = readline("> ");
	while (line)
	{
		if (ft_strncmp(line, limit, (ft_strlen(line) - 1)) == 0
			&& (ft_strlen(line)) == ft_strlen(limit))
			break ;
		line = ft_strjoin_allocs1(line, "\n", 1);
		write(fd, line, ft_strlen(line));
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	else
	{
		ft_putstr_fd("minishell: syntax error: ", STDERR);
		ft_putstr_fd("unexpected end of file\n", STDERR);
	}
}

static int	ft_here_doc_2(int fd[2], char *limit, t_data *data)
{
	int				status;
	pid_t			pid;

	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		close(fd[0]);
		signal(SIGINT, ft_here_doc_signal);
		ft_here_doc_loop(limit, fd[1]);
		ft_free_all(data);
		data = NULL;
		close(fd[1]);
		exit(0);
	}
	ft_get_exit_code(pid, &status, data);
	return (0);
}

int	ft_here_doc(char *limit, t_cmd *cmd, t_data *data)
{
	int			fd[2];

	fd[0] = open(".temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[0] == -1)
		return (1);
	if (!limit)
		return (1);
	if (pipe(fd) == -1)
		return (1);
	if (ft_here_doc_2(fd, limit, data) == 1)
	{
		close(fd[0]);
		close(fd[1]);
		return (write(STDERR, "Here doc error\n", STDERR));
	}
	cmd->fds->infile = fd[0];
	cmd->infile_flag = 1;
	unlink(".temp");
	close(fd[1]);
	return (0);
}

/*
int until_special_char(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_special_character(str[i]) == 0)
		i++;
	return (i);
}

static char *copy_line_heredoc(char *line, t_cmd *cmd)
{
    int i;
    int j;
    char *res;
    char *tmp;

	tmp = line;
    res = calloc(ft_strlen(line) + 1, sizeof(char));
    if (!res)
        return (NULL);
    i = 0;
    j = 0;
    while (line[i])
    {
        if (line[i] != '$')
            res[j++] = line[i++];
        else
        {
            res = ft_strjoin_allocs1(res,
					ft_getenv(line + i + 1, *(cmd->env->env)), 0);
            j = ft_strlen(res);
            i += until_special_char(line + i + 1) + 1;
        }
    }
    res = ft_strjoin_allocs1(res, "\n", 1);
	free(tmp);
	tmp = NULL;
    return (res);
}*/
