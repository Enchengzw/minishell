/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:14:54 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/23 18:08:39 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_shell_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		//g_exit_code = 130;
	}
	return ;
}

static void	ft_child_handler(int signal)
{
	if (signal == SIGINT)
		//g_exit_code = 130;
		return ;
	if (signal == SIGQUIT)
	{
		write(1, "Quit: 3\n", 9);
		//g_exit_code = 131;
	}
	return ;
}

void	ft_child_signals()
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &ft_child_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}

void	ft_main_signals()
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &ft_shell_handler;
	//signal(SIGCHLD, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}
