/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:06:35 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/02 15:55:12 by ezhou            ###   ########.fr       */
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

static	int	ft_update_pwd(t_env *env)
{
	int		i;
	char	*temp;
	char	*cwd;

	cwd = ft_current_path();
	if (!cwd)
		return (ERROR);
	i = 0;
	while (env->env[0][i])
	{
		if (!ft_strncmp(env->env[0][i], "PWD", 3))
		{
			temp = ft_strjoin("PWD=", cwd);
			if (!temp)
				return (free(cwd), ERROR);
			free(env->env[0][i]);
			env->env[0][i] = temp;
		}
		i++;
	}
	return (SUCCESS);
}

static int		ft_default_cd(t_cmd **cmd)
{
	if (!getenv("HOME"))
	{
		printf("bash: cd: HOME not set\n");
		return (ERROR);
	}
	chdir(getenv("HOME"));
	if (ft_update_pwd((*cmd)->env))
		return (ERROR);
	return (SUCCESS);
}

static	int	ft_update_oldpwd(t_env *env)
{
	int		i;
	char	*temp;
	char	*cwd;

	cwd = ft_current_path();
	if (!cwd)
		return (ERROR);
	i = 0;
	while (env->env[0][i])
	{
		if (!ft_strncmp(env->env[0][i], "OLDPWD", 6))
		{
			temp = ft_strjoin("OLDPWD=", cwd);
			if (!temp)
				return (free(cwd), ERROR);
			free(env->env[0][i]);
			env->env[0][i] = temp;
		}
		i++;
	}
	return (SUCCESS);
}


int	ft_cd(t_cmd **cmd)
{
	char	*temp;

	(*cmd)->num_arg = ft_dpointer_size((*cmd)->arg);
	temp = ft_strdup((*cmd)->arg[1]);
	if (!temp)
		return (ft_putstr_fd("Malloc Error\n", 2), ERROR);
	ft_update_oldpwd((*cmd)->env);
	if ((*cmd)->num_arg == 1)
	{
		if (ft_default_cd(cmd))
			return (free(temp), ERROR);
		return (free(temp), SUCCESS);
	}
	if (chdir(temp) == -1)
		printf("bash: cd: %s: No such file or directory\n", temp);
	else
	{
		if (ft_update_pwd((*cmd)->env))
			return(free(temp), ERROR);
		return (free(temp), SUCCESS);
	}
	return (free(temp), ERROR);
}

/* int main(int argc, char **argv, char **env)
{
	t_cmd *cmd;
	char **dupe;

	dupe = ft_dpointer_dupe(env);
	cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	cmd->cmd_path = "/bin/ls";
	cmd->arg = (char **)malloc(sizeof(char *) * 3);
	cmd->arg[0] = "cd";
	cmd->arg[1] = "/Users/ezhou/minishell/src/";
	cmd->arg[2] = 0;
	cmd->env = (t_env *)malloc(sizeof(t_env) * 1);
	cmd->env->env_size = ft_dpointer_size(env);
	cmd->env->env = &dupe;
	cmd->num_arg = 2;
	printf("%s\n", ft_current_path());
	ft_cd(&cmd);
	printf("%s\n", ft_current_path());
	return (0);
} */