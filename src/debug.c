/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:20:04 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/08 13:48:30 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_print_node(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd)
	{
		j = 0;
		ft_putstr_fd("i :", 2);
		ft_putnbr_fd(i, 2);
		ft_putchar_fd('\n', 2);
		/* ft_putstr_fd("cmd_path: ", 2);
		ft_putstr_fd(cmd->cmd_path, 2);
		ft_putstr_fd("\n", 2); */
		while(cmd->arg[j])
		{
			ft_putstr_fd("arg[", 2);
			ft_putnbr_fd(j, 2);
			ft_putstr_fd("]: ", 2);
			ft_putendl_fd(cmd->arg[j], 2);
			j++;
		}
		ft_putnbr_fd(cmd->fds->infile, 2);
		ft_putstr_fd(" ", 2);
		ft_putnbr_fd(cmd->fds->outfile, 2);
		ft_putstr_fd("\n", 2);
		cmd = cmd->next;
		i++;
	}
}