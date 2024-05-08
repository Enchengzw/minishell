/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:17:49 by rauferna          #+#    #+#             */
/*   Updated: 2024/05/08 13:13:54 by ezhou            ###   ########.fr       */
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
		g_exit_code = ft_execute(data);
		if (data->cmd)
		{
			free(data->user_input);
			ft_free_list(data->cmd);
			data->cmd = NULL;
		}
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
//cuando haces Ctrl + C no debe aparecer ^C (opcional)
//Los builtins no redirigen el outfile bien
//si pones por ejemplo echo $PATH | tr ':' '\n' no le llega el path
//No estan arreglados unos casos que habias arreglado en cd, porque he tenido que arreglar el de echo
//cuando pongas echo $? que muestre el return del antiguo comando
//Los builtins los he puesto yo para ir probando ciertos casos y faltan cosas, por ejemplo en exit, no se a que se refiere con t_cmd **start
//las señales no sale con control c a la primera cuando ejecutas varios comandos

