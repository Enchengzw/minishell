/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:14:54 by ezhou             #+#    #+#             */
/*   Updated: 2024/04/24 16:09:16 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_shell_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);	
		rl_on_new_line();
		rl_replace_line("", 0);	
		rl_redisplay();
		g_exit_code = 130;
	}
	return ;
}

static void	ft_child_handler(int signal)
{
	if (signal == SIGINT)
		g_exit_code = 130;
	else if (signal == SIGQUIT)
	{
		write(1, "Quit: 3\n", 10);
		g_exit_code = 131;
	}
	return ;
}

void	ft_child_signals()
{
	struct sigaction	sa;

	sa.sa_handler = &ft_child_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}

void	ft_main_signals()
{
	struct sigaction	sa;

	sa.sa_handler = &ft_shell_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}
