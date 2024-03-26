/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:06:35 by ezhou             #+#    #+#             */
/*   Updated: 2024/03/22 15:35:30 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	while (env->env[i])
	{
		if (!ft_strncmp(env->env[i], "OLDPWD", 6))
		{
			temp = ft_strjoin("OLDPWD=", cwd);
			free(env->env[i]);
			env->env[i] = temp;
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
	while (env->env[i])
	{
		if (!ft_strncmp(env->env[i], "PWD", 3))
		{
			temp = ft_strjoin("PWD=", cwd);
			free(env->env[i]);
			env->env[i] = temp;
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

/*  int main(int argc, char **argv, char **env)
{
	t_cmd *cmd;
	int	i = 0;

	cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	cmd->cmd_path = "/bin/cd";
	cmd->arg = (char **)malloc(sizeof(char *) * 3);
	cmd->arg[0] = "cd";
	cmd->arg[1] = "/Users/ezhou/minishell/src";
	cmd->arg[2] = 0;
	cmd->env = (t_env *)malloc(sizeof(t_env) * 1);
	cmd->env->env_size = ft_dpointer_size(env);
	cmd->env->env = (char **)malloc(sizeof(char *) * cmd->env->env_size);
	while (env[i])
	{
		cmd->env->env[i] = ft_strdup(env[i]);
		i++;
	}
	cmd->num_arg = 1;
	ft_cd(&cmd);
	i = 0;
	ft_pwd();
	return (0);
}  */