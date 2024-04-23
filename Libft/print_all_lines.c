/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:44:22 by ezhou             #+#    #+#             */
/*   Updated: 2023/11/20 10:46:34 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_all_lines(int fd)
{
	char	*line;

	line = "";
	while (line)
	{
		line = get_next_line(fd);
		ft_printf("%s\n", line);
		free(line);
	}
}
