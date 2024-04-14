/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:46:53 by rauferna          #+#    #+#             */
/*   Updated: 2024/04/12 11:13:15 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_here_doc(char **args, int i, t_cmd *cmd)
{
	char	*line;
	char	*limit;
	int		fd;
	//si sales con Ctrl + D segfault
	if (!args[i + 1] && ft_strlen(args[i]) <= 2)
	{
		error_syntax("newline");
		return ;
	}
	if (ft_strlen(args[i]) > 2)
		limit = args[i] + 2;	
	else if (args[i + 1] && ft_strlen(args[i]) == 2)
		limit = args[i + 1];
	fd = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(2, "> ", 2);
	line = get_next_line(0);
	while (1)
	{
		if (ft_strncmp(line, limit, (ft_strlen(line) - 1)) == 0
			&& (ft_strlen(line) - 1) == ft_strlen(limit))
			break ;
		write(2, "> ", 2);
		write(fd, line, ft_strlen(line));
		line = get_next_line(0);
	}
	cmd->fds->here_document = fd;
	close(fd);
	unlink("temp");
}

static void	continue_redirections(char **args, int *i, t_cmd *cmd)
{
	if (ft_strncmp(args[*i], "<", 1) == 0)
	{
		if (args[*i][*i + 1])
			cmd->fds->infile = openfile(&args[*i][*i + 1], 1);
		else
			cmd->fds->infile = openfile(args[*i + 1], 1);
	}
	else if (ft_strncmp(args[*i], ">", 1) == 0)
	{
		if (args[*i][*i + 1])
			cmd->fds->outfile = openfile(&args[*i][*i + 1], 2);
		else
			cmd->fds->outfile = openfile(args[*i + 1], 2);
	}
	else
	{
		cmd->fds->infile = open(args[*i], O_RDONLY, 0644);
		if (cmd->fds->infile < 0
			&& ft_strncmp(args[*i - 1], "<<", 2) != 0)
			error_fnf(args[*i]);
	}
}

int	check_redirections(char **args, int i, t_cmd *cmd)
{
	cmd->fds = malloc(sizeof(t_fds));
	if (!cmd->fds)
		return (-1);
	if (!args[i + 1] && ft_strlen(args[i]) <= 2)
	{
		if (args[i][0] == '<' || args[i][0] == '>')
			error_syntax(args[i]);
		else
			error_fnf(args[i]);
		return (1);
	}
	if (ft_strncmp(args[i], ">>", 1) == 0)
	{
		if (args[i][i + 1])
			cmd->fds->outfile = openfile(&args[i][i + 1], 3);
		else
			cmd->fds->outfile = openfile(args[i + 1], 3);
	}
	else if (ft_strncmp(args[i], "<<", 2) == 0)
		ft_here_doc(args, i, cmd);
	else
		continue_redirections(args, &i, cmd);
	if (cmd->fds->infile >= 0)
		cmd->file_flag = 1;
	return (cmd->fds->infile);
}


