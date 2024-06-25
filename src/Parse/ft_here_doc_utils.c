/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:52:20 by ezhou             #+#    #+#             */
/*   Updated: 2024/06/25 21:01:13 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_get_exit_code(int pid, int *status)
{
	int	pid_check;

	while (1)
	{
		pid_check = waitpid(pid, status, 0);
		if (pid_check > 0)
			break ;
	}
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

char	*ft_here_doc_check(char **args, char *res, int i)
{
	char	*limit;

	if (check_start(args, res, i) == 1)
		return (NULL);
	if (ft_strlen(res) > 2)
		limit = res + 2;
	else if (args[i + 1] && ft_strlen(res) == 2)
		limit = args[i + 1];
	return (limit);
}
