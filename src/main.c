/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:17:49 by rauferna          #+#    #+#             */
/*   Updated: 2024/05/14 17:58:12 by rauferna         ###   ########.fr       */
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
		data->exit_code = ft_execute(data);
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

//si pones por ejemplo echo $PATH | tr ':' '\n' no le llega el path VUELVE A PASAR
//cuando pongas echo $? que muestre el return del antiguo comando devuelve 0 si viene de execve en caso de fallo
//ej pones cat asdsa (ese file no existe) y te devuelve 1 bash, pero minishell devuelve 0
//he cambiado la funcion de getenv, he puesto una funcion ft_strlen_no_spaces, porque si pones echo "     $PATH   "no expandía, y bash si lo hace->
//no creo que afecte porque no se usan espacios en las variables de entorno. pero verifica si te afecta

