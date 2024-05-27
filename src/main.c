/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:17:49 by rauferna          #+#    #+#             */
/*   Updated: 2024/05/27 12:26:22 by ezhou            ###   ########.fr       */
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
	data->exit_code = 0;
	data->std_in = dup(STDIN_FILENO);
	data->std_out = dup(STDOUT_FILENO);
	return (data);
}

void	ft_main_loop(t_data *data)
{
	while (1)
	{
		ft_main_signals();
		data->user_input = readline(GREEN_TEXT "Minishell$: " RESET_TEXT);
		if (!data->user_input)
			ft_exit_error("exit\n", ERROR, data);
		add_history(data->user_input);
		ft_parse(data->user_input, data);
		ft_child_signals();
		ft_execute(data);
		if (data->cmd)
		{
			free(data->user_input);
			ft_free_list(data->cmd);
			data->cmd = NULL;
		}
		ft_format_exit_code(&(data->exit_code));
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argv;
	if (argc > 1)
		return (ft_putstr_fd("Too many arguments\n", 2), ERROR);
	data = ft_init(env);
	if (!data)
		return (ft_putstr_fd("Malloc Error\n", STDERR), ERROR);
	ft_main_loop(data);
	ft_free_all(data);
	return (0);
}
