/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:19:32 by ychng             #+#    #+#             */
/*   Updated: 2024/03/20 05:30:00 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_no_args(char **envp)
{
	handle_oldpwd(envp);
	move_to_home_directory();
	handle_pwd(envp);
	return (0);
}

static void	handle_dot(char **envp)
{
	handle_oldpwd(envp);
}

static void	handle_dotdot(char **envp)
{
	handle_oldpwd(envp);
	move_to_parent_directory();
	handle_pwd(envp);
}

int	blt_cd(char **envp, t_subtoken_node *args)
{
	if (args == NULL)
		return (handle_no_args(envp));
	if (args->next == NULL)
	{
		if (!ft_strcmp(args->subtoken, ".."))
			handle_dotdot(envp);
		else if (!ft_strcmp(args->subtoken, "."))
			handle_dot(envp);
	}
	return (0);
}
