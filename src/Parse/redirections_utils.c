/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:52:20 by ezhou             #+#    #+#             */
/*   Updated: 2024/07/02 20:38:20 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_get_exit_code(int pid, int *status, t_data *data)
{
	int	pid_check;

	while (1)
	{
		pid_check = waitpid(pid, status, 0);
		if (pid_check > 0)
			break ;
		data->is_interrupted = 1;
	}
}

void	ft_free_redirection_space(char *arg, char **arg2, int *i)
{
	if (ft_strcmp(arg, ">>") == 0 || ft_strcmp(arg, "<<") == 0
		|| ft_strncmp(arg, ">", 2) == 0 || ft_strcmp(arg, "<") == 0)
	{
		free(*arg2);
		(*arg2) = NULL;
		(*i)++;
	}
	else if (ft_strncmp(arg, ">>>", 3) == 0 || ft_strncmp(arg, "<<<", 3) == 0)
	{
		free(*arg2);
		(*arg2) = NULL;
		(*i)++;
	}
}

/*
char 	*ft_strcopy_until_redirection(char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_calloc(ft_strlen(str), sizeof(char));
	if (!res)
		return (NULL);
	while (str[i] && (str[i] == '>' || str[i] == '<'))
	{
		res[i] = str[i];
		i++;
	}
	while (str[i] && str[i] != '>' && str[i] != '<')
	{
		res[i] = str[i];
		i++;
	}
	return (res);
}
*/
