/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_sorted_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:22:08 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/02 11:57:16 by ezhou            ###   ########.fr       */
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

int	ft_print_sorted_env(char **env)
{
	char	**dupe;
	char	*label;
	char	*value;
	int		i;

	label = NULL;
	value = NULL;
	i = 0;
	dupe = ft_dpointer_dupe(env);
	if (!dupe)
		return (ERROR);
	ft_sort(dupe);
	while (dupe[i])
	{
		label = ft_get_label(dupe[i]);
		value = ft_get_value(dupe[i]);
		if (!label || !value)
			return (ft_free_char(dupe), free(label), free(value), ERROR);
		printf("declare -x %s=\"%s\"\n", label, value);
		ft_clean(label);
		ft_clean(value);
		i++;
	}
	ft_free_char(dupe);
	return (SUCCESS);
}

/* int main(int argc, char **argv, char **env)
{
	ft_print_sorted_env(env);
	return (0);
} */