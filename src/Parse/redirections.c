/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:46:53 by rauferna          #+#    #+#             */
/*   Updated: 2024/06/04 20:16:07 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//return 1 OK
//0 only initialized
//return -1 ERROR
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
			return (ERROR);
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

static int	ft_check_errors(char **args, int *i)
{
	if (!args[*i + 1] && ((ft_strlen(args[*i]) == 2 && (args[*i][1] == '<'
				|| args[*i][1] == '>')) || ft_strlen(args[*i]) == 1))
	{
		ft_error_syntax(args[*i]);
		return (-1);
	}
	else if (ft_strncmp(args[*i], ">>>", 3) == 0
		|| ft_strncmp(args[*i], "<<<<", 4) == 0)
	{
		ft_error_syntax(args[*i]);
		return (-1);
	}
	else
		return (1);
}

static char	*check_redirection_nospaces(char **args, int *i, t_cmd *cmd)
{
	int		k;
	char	*res;

	k = 0;
	res = NULL;
	cmd->redirect_then = -1;
	if (args[*i][0] == '<' || args[*i][0] == '>')
		return (args[*i]);
	while (args[*i][k] && args[*i][k] != '<' && args[*i][k] != '>')
		k++;
	res = ft_strdup(args[*i] + k);
	args[*i] = ft_substr(args[*i], 0, k);
	cmd->redirect_then = 1;
	return (res);
}

int	ft_check_redirections(char **args, int i, t_cmd *cmd, t_data *data)
{
	char	*res;

	if (ft_redirections_init(cmd, args, &i, data) == 1
		|| ft_check_errors(args, &i) == -1)
		return (-1);
	res = check_redirection_nospaces(args, &i, cmd);
	if (ft_strncmp(res, ">>", 2) == 0)
	{
		if (ft_strlen(res) == 2)
			cmd->fds->outfile = ft_openfile(args[i + 1], 3);
		else
			cmd->fds->outfile = ft_openfile(res + 2, 3);
		cmd->outfile_flag = 1;
	}
	else if (ft_strncmp(res, "<<", 2) == 0)
	{
		if (ft_here_doc(args, res, i, cmd) == 1)
			return (free(res), -1);
		return (free(res), 2);
	}
	continue_redirections(args, &i, res, cmd);
	if (cmd->fds->outfile == -1 || cmd->fds->infile == -1)
		return (free(res), -1);
	return (free(res), 1);
}
