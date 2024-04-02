/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:06:35 by ezhou             #+#    #+#             */
/*   Updated: 2024/04/02 18:04:26 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static	char	*ft_current_path(void)
{
	char	*cwd;

	cwd = ft_calloc(PATH_MAX, 1);
	if (!cwd)
		return (ft_putstr_fd("Malloc Error\n", 2), NULL);
	if (getcwd(cwd, PATH_MAX))
	{
		return (cwd);
	}
	else
	{
		ft_putstr_fd("Getcwd Error\n", 2);
		return (NULL);
	}
}

static	void	ft_update_oldpwd(t_env *env)
{
	int		i;
	char	*temp;
	char	*cwd;

	cwd = ft_current_path();
	if (!cwd)
		return ;
	i = 0;
	while (env->env[0][i])
	{
		if (!ft_strncmp(env->env[0][i], "OLDPWD", 6))
		{
			temp = ft_strjoin("OLDPWD=", cwd);
			free(env->env[0][i]);
			env->env[0][i] = temp;
		}
		i++;
	}
}

static	void	ft_update_pwd(t_env *env)
{
	int		i;
	char	*temp;
	char	*cwd;

	cwd = ft_current_path();
	if (!cwd)
		return ;
	i = 0;
	while (env->env[0][i])
	{
		if (!ft_strncmp(env->env[0][i], "PWD", 3))
		{
			temp = ft_strjoin("PWD=", cwd);
			free(env->env[0][i]);
			env->env[0][i] = temp;
		}
		i++;
	}
}

int	ft_cd(t_cmd **cmd)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_strdup((*cmd)->arg[1]);
	ft_update_oldpwd((*cmd)->env);
	if ((*cmd)->num_arg == 0)
	{
		chdir(getenv("HOME"));
		ft_update_pwd((*cmd)->env);
		return (SUCCESS);
	}
	if (chdir(temp) == -1)
		printf("bash: cd: %s: No such file or directory\n", temp);
	else
	{
		free(temp);
		ft_update_pwd((*cmd)->env);
		return (SUCCESS);
	}
	free(temp);
	return (ERROR);
}
