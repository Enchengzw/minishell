/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:17:49 by rauferna          #+#    #+#             */
/*   Updated: 2024/04/19 11:22:01 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_data	*ft_init(char **env)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (ft_putstr_fd("Malloc Error\n", STDERR), NULL);
	data->user_input = 0;
	data->env = ft_dpointer_dupe(env);
	if (!data->env)
		return (ft_putstr_fd("Malloc Error\n", STDERR), free(data), NULL);
	data->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!data->cmd)
		return (ft_putstr_fd("Malloc Error\n", STDERR), ft_free_char(data->env),
			free(data), NULL);
	data->cmd->fds = ft_calloc(1, sizeof(t_fds));
	if (!data->cmd->fds)
		return (ft_putstr_fd("Malloc Error\n", STDERR), NULL);
	return (data);
}

void	ft_main_loop(t_data *data)
{
	while (1)
	{
		ft_main_signals();
		data->user_input = readline(GREEN_TEXT "Minishell$: " RESET_TEXT);
		if (!data->user_input)
			ft_exit_error("exit", ERROR);
		add_history(data->user_input);
		ft_parse(data->user_input, data);
		ft_child_signals();
		g_exit_code = ft_execute(data);
		ft_free_content(data);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	if (argc > 1)
		return (ft_putstr_fd("Too many arguments\n", 2), ERROR);
	data = ft_init(env);
	if (!data)
		return (ft_putstr_fd("Malloc Error\n", STDERR), ERROR);
	ft_main_loop(data);
	// ft_free_all
	return (0);
}

//comprobar permisos antes de ejecutar
//cuando haces Ctrl + C no debe aparecer ^C
//Cerrar parser cuando haya error