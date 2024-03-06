/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 03:40:06 by ychng             #+#    #+#             */
/*   Updated: 2024/03/06 23:06:07 by ychng            ###   ########.fr       */
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

int	count_params_size(t_subtoken_list *params_list)
{
	int				export_envp_size;
	t_subtoken_node	*current;

	export_envp_size = 0;
	current = params_list->head;
	while (current)
	{
		if (!validate_entry_name(current->subtoken))
			break ;
		if (getenv(current->subtoken) == NULL)
			export_envp_size++;
		current = current->next;
	}
	return (export_envp_size);
}

void	from_envp(char **export_envp, char **envp)
{
	while (*envp)
		*export_envp++ = ft_strdup(*envp++);
	*export_envp = NULL;
}

void	from_params(char **export_envp, t_subtoken_list *params_list)
{
	t_subtoken_node	*current;

	current = params_list->head;
	while (current)
	{
		if (!validate_entry_name(current->subtoken))
			return ;
		*export_envp++ = ft_strdup(current->subtoken);
		current = current->next;
	}
	*export_envp = NULL;
}
