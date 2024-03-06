/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:42:41 by ychng             #+#    #+#             */
/*   Updated: 2024/03/07 02:45:14 by ychng            ###   ########.fr       */
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

int	count_params_size(t_subtoken_node *params)
{
	int	export_envp_size;

	export_envp_size = 0;
	while (params)
	{
		if (!validate_entry_name(params->subtoken))
			break ;
		if (getenv(params->subtoken) == NULL)
			export_envp_size++;
		params = params->next;
	}
	return (export_envp_size);
}

void	from_envp(char **dest, char **envp)
{
	while (*envp)
		*dest++ = ft_strdup(*envp++);
	*dest = NULL;
}

void	from_params(char **dest, t_subtoken_node *params)
{
	while (params)
	{
		if (!validate_entry_name(params->subtoken))
			return ;
		*dest++ = ft_strdup(params->subtoken);
		params = params->next;
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
