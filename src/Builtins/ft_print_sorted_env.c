/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_sorted_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:22:08 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/27 13:05:42 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static void	ft_str_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	ft_sort(char **to_sort)
{
	int	i;
	int	j;

	i = 0;
	while (to_sort[i])
	{
		j = i + 1;
		while (to_sort[j])
		{
			if (ft_strncmp(to_sort[i], to_sort[j], ft_strlen(to_sort[i])) > 0)
				ft_str_swap(&to_sort[i], &to_sort[j]);
			j++;
		}
		i++;
	}
}

static int	ft_printer(char *to_print)
{
	char	*label;
	char	*value;

	value = NULL;
	label = ft_get_label(to_print);
	if (!label)
		return (ERROR);
	if (ft_strcontains(to_print, '=') && to_print[ft_strlen(label) + 1])
	{
		value = ft_get_value(to_print);
		if (!value)
			return (free(label), ERROR);
		printf("declare -x %s=\"%s\"\n", label, value);
	}
	else
		printf("declare -x %s=\"\"", label);
	ft_clean(label);
	ft_clean(value);
	return (SUCCESS);
}

int	ft_print_sorted_env(char **env)
{
	char	**dupe;
	int		i;

	i = 0;
	dupe = ft_dpointer_dupe(env);
	if (!dupe)
		return (ERROR);
	ft_sort(dupe);
	while (dupe[i])
	{
		if (ft_printer(dupe[i]))
			return (ft_free_char(dupe), SUCCESS);
		i++;
	}
	return (ft_free_char(dupe), SUCCESS);
}

/* int main(int argc, char **argv, char **env)
{
	ft_print_sorted_env(env);
	return (0);
} */