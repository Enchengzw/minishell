/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:27:08 by ezhou             #+#    #+#             */
/*   Updated: 2024/03/26 17:57:04 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_execute(t_data *data)
{	
	int	code;
	
	code = ft_check_data(data);
	if (code != INT_MIN)
		return (code);
	if (ft_create_pipes(data))
		return (ERROR);
	ft_link_io(data);
	return (1);
}