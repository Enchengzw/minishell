/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:31:05 by rauferna          #+#    #+#             */
/*   Updated: 2024/06/21 11:20:48 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// d = doubquotes, s = singlequotes, r = redir, n = normal, m = dollar v = ~
// h = heredoc

int	ft_len_type(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		{
			if (str[i] == 34 || str[i] == 39)
			{
				i++;
				while (str[i] && str[i] != 34 && str[i] != 39)
					i++;
			}
			i++;
		}
		if (str[i])
			j++;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
		i++;
	}
	return (j);
}

static int	ft_check_type2(const char *s, char type)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (!s[i])
		return (0);
	while (s[i] && (s[i] != ' ' && s[i] != '\t' && s[i] != '\n'))
	{
		if (s[i] == type)
			num = 1;
		if ((type == 34 || type == 39) && num == 0)
		{
			if (s[i] == '>' || s[i] == '<' || s[i] == '|')
				return (0);
		}
		i++;
	}
	return (num);
}

void	ft_check_type(const char *s, t_cmd *cmd, int *i, int *k)
{
	if (ft_check_type2(s + *k, 39) == 1)
		cmd->type[*i] = 's';
	else if (ft_check_type2(s + *k, 34) == 1)
		cmd->type[*i] = 'd';
	else if (ft_check_type2(s + *k, '>') == 1
		|| ft_check_type2(s + *k + 1, '<') == 1)
		cmd->type[*i] = 'h';
	else if (ft_check_type2(s + *k, '>') == 1
		|| ft_check_type2(s + *k, '<') == 1)
		cmd->type[*i] = 'r';
	else if (ft_check_type2(s + *k, '$') == 1)
		cmd->type[*i] = 'm';
	else if (ft_check_type2(s + *k, '~') == 1)
		cmd->type[*i] = 'v';
	else
		cmd->type[*i] = 'n';
}

int	ft_is_builtin(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
		return (0);
	else if (ft_strcmp(command, "echo") == 0)
		return (0);
	else if (ft_strcmp(command, "env") == 0)
		return (0);
	else if (ft_strcmp(command, "exit") == 0)
		return (0);
	else if (ft_strcmp(command, "export") == 0)
		return (0);
	else if (ft_strcmp(command, "pwd") == 0)
		return (0);
	else if (ft_strcmp(command, "unset") == 0)
		return (0);
	else
		return (1);
}

int	ft_openfile(char *file, int type)
{
	int	fd[2];

	if (type == 1)
	{
		fd[0] = open(file, O_RDONLY, 0644);
		if (fd[0] == -1)
			ft_error_fnf(file);
		return (fd[0]);
	}
	else if (type == 2)
	{
		fd[1] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[1] == -1)
			ft_error_fnf(file);
		return (fd[1]);
	}
	else if (type == 3)
	{
		fd[1] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd[1] == -1)
			ft_error_fnf(file);
		return (fd[1]);
	}
	return (-1);
}
