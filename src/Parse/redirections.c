/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:46:53 by rauferna          #+#    #+#             */
/*   Updated: 2024/07/02 21:11:07 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//return 1 OK
//0 only initialized
//return -1 ERROR
//return -2 Bad < or >
//return 2 HERE_DOC
static int	ft_redirections_init(t_cmd *cmd, char **args, int *i, t_data *data)
{
	if (cmd->fds)
	{
		if (cmd->infile_flag == 1 && ft_strchr(args[*i], '<') != NULL)
			close(cmd->fds->infile);
		if (cmd->outfile_flag == 1 && ft_strchr(args[*i], '>') != NULL)
			close(cmd->fds->outfile);
	}
	else
	{
		cmd->fds = ft_calloc(1, sizeof(t_fds));
		if (!cmd->fds)
		{
			ft_putstr_fd("Malloc Error\n", STDERR);
			return (ERROR);
		}
	}
	cmd->fds->std_in = data->std_in;
	cmd->fds->std_out = data->std_out;
	return (SUCCESS);
}

static void	continue_redirections(char **args, int *i, char *res, t_cmd *cmd)
{
	if (ft_strncmp(res, ">>", 2) != 0
		&& ft_strncmp(res, "<<", 2) != 0)
	{
		if (ft_strncmp(res, "<", 1) == 0)
		{
			if (ft_strlen(res) == 1)
				cmd->fds->infile = ft_openfile(args[*i + 1], 1);
			else
				cmd->fds->infile = ft_openfile(res + 1, 1);
			cmd->infile_flag = 1;
		}
		else if (ft_strncmp(res, ">", 1) == 0)
		{
			if (ft_strlen(res) == 1)
				cmd->fds->outfile = ft_openfile(args[*i + 1], 2);
			else
				cmd->fds->outfile = ft_openfile(res + 1, 2);
			cmd->outfile_flag = 1;
		}
	}
}

static int	ft_check_errors(char *res, t_cmd *cmd, int *i)
{
	if (!cmd->arg[*i + 1] && ((ft_strlen(res) == 2 && (res[1] == '<'
					|| res[1] == '>')) || ft_strlen(res) == 1))
	{
		ft_error_syntax(res);
		free(res);
		return (-1);
	}
	else if (ft_strncmp(res, ">>>", 3) == 0
		|| ft_strncmp(res, "<<<<", 4) == 0)
	{
		ft_error_syntax(res);
		ft_free_redirection_space(cmd->arg[*i], &(cmd->arg[*i + 1]), i);
		free(res);
		return (-1);
	}
	else
		return (1);
}

static char	*check_redirection_nospaces(char **args, int *i, int *redirect)
{
	int		k;
	char	*tmp;
	char	*res;

	k = 0;
	res = NULL;
	(*redirect) = -1;
	if (args[*i][0] == '<' || args[*i][0] == '>')
		return (args[*i]);
	while (args[*i][k] && args[*i][k] != '<' && args[*i][k] != '>')
		k++;
	res = ft_strdup(args[*i] + k);
	if (!res)
	{
		ft_putstr_fd("Malloc Error\n", STDERR);
		return (NULL);
	}
	tmp = args[*i];
	args[*i] = ft_substr(args[*i], 0, k);
	free(tmp);
	tmp = NULL;
	(*redirect) = 1;
	return (res);
}

int	ft_check_redirections(int *i, t_cmd *cmd, t_data *data, int *redirect)
{
	char	*res;

	res = check_redirection_nospaces(cmd->arg, i, redirect);
	if (ft_check_errors(res, cmd, i) == -1)
		return (-2);
	if (ft_redirections_init(cmd, cmd->arg, i, data) == 1)
		return (-1);
	if (ft_strncmp(res, ">>", 2) == 0)
		ft_check_double_greather(cmd->arg, res, *i, cmd);
	else if (ft_strncmp(res, "<<", 2) == 0)
	{
		if (ft_here_doc(ft_here_doc_check(res, i, cmd), cmd, data) == 1)
			return (ft_free_redirection_space(cmd->arg[*i],
					&(cmd->arg[*i + 1]), i), free(res), -1);
		ft_free_redirection_space(cmd->arg[*i], &(cmd->arg[*i + 1]), i);
		return (free(res), 2);
	}
	continue_redirections(cmd->arg, i, res, cmd);
	ft_free_redirection_space(cmd->arg[*i], &(cmd->arg[*i + 1]), i);
	if (cmd->fds->outfile == -1 || cmd->fds->infile == -1)
		return (free(res), -1);
	return (free(res), 1);
}
