/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:52:20 by ezhou             #+#    #+#             */
/*   Updated: 2024/06/25 12:18:58 by ezhou            ###   ########.fr       */
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
