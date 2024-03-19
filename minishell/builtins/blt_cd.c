/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:19:32 by ychng             #+#    #+#             */
/*   Updated: 2024/03/20 05:05:21 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_cwd(void)
{
	char	*cwd;
	int		size;

	cwd = NULL;
	size = 1024;
	while (size < 4096)
	{
		cwd = malloc(size);
		if (!cwd)
		{
			printf("malloc failed for cwd\n");
			exit(-1);
		}
		if (getcwd(cwd, size))
			break ;
		free(cwd);
		size *= 2;
	}
	if (cwd == NULL)
	{
		printf("getcwd failed\n");
		exit(-1);
	}
	return (cwd);
}

char	*update_oldpwd(void)
{
	char	*cwd;
	char	*new_entry;

	cwd = get_cwd();
	new_entry = ft_strjoin("OLDPWD=", cwd, "");
	if (!new_entry)
	{
		printf("ft_strjoin failed for *envp\n");
		free(cwd);
		exit(-1);
	}
	free(cwd);
	return (new_entry);
}

void	handle_oldpwd(char **envp)
{
	while (*envp)
	{
		if (!ft_strncmp(*envp, "OLDPWD", 6) && is_equal((*envp)[6]))
		{
			free(*envp);
			*envp = update_oldpwd();
		}
		envp++;
	}
}

char	*update_pwd(void)
{
	char	*cwd;
	char	*new_entry;

	cwd = get_cwd();
	new_entry = ft_strjoin("PWD=", cwd, "");
	if (!new_entry)
	{
		printf("ft_strjoin failed for new_entry\n");
		free(cwd);
		exit(-1);
	}
	free(cwd);
	return (new_entry);
}

void	handle_pwd(char **envp)
{
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PWD", 3) && is_equal((*envp)[3]))
		{
			free(*envp);
			*envp = update_pwd();
		}
		envp++;
	}
}

void	move_to_home_directory(void)
{
	char	*home_dir;

	home_dir = getenv("HOME");
	if (!home_dir)
		printf("getenv failed for home+dir\n");
	if (chdir(home_dir) != 0)
		printf("chdir failed\n");
}

int	handle_no_args(char **envp)
{
	handle_oldpwd(envp);
	move_to_home_directory();
	handle_pwd(envp);
	return (0);
}

int	blt_cd(char **envp, t_subtoken_node *args)
{
	if (args == NULL)
		return (handle_no_args(envp));
	return (0);
}
