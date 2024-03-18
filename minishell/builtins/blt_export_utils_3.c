/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:42:41 by ychng             #+#    #+#             */
/*   Updated: 2024/03/18 22:02:25 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_envp_size(char **envp)
{
	int	envp_size;

	envp_size = 0;
	while (envp[envp_size])
		envp_size++;
	return (envp_size);
}

int	count_args_size(t_subtoken_node *args)
{
	int	export_envp_size;

	export_envp_size = 0;
	while (args)
	{
		if (!validate_entry_name(args->subtoken))
			break ;
		if (getenv(args->subtoken) == NULL)
			export_envp_size++;
		args = args->next;
	}
	return (export_envp_size);
}

void	from_envp(char **dest, char **envp)
{
	while (*envp)
		*dest++ = ft_strdup(*envp++);
	*dest = NULL;
}

void	from_args(char **dest, t_subtoken_node *args)
{
	while (args)
	{
		if (!validate_entry_name(args->subtoken))
			return ;
		*dest++ = ft_strdup(args->subtoken);
		args = args->next;
	}
	*dest = NULL;
}

int	get_max_name_len(char **export_envp)
{
	int	max_len;
	int	len;

	max_len = 0;
	while (*export_envp)
	{
		len = ft_strcspn(*export_envp, "=");
		if (max_len < len)
			max_len = len;
		export_envp++;
	}
	return (max_len);
}
