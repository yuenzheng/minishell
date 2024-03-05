/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 03:40:06 by ychng             #+#    #+#             */
/*   Updated: 2024/03/06 04:03:59 by ychng            ###   ########.fr       */
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

bool	validate_env_name(char *subtoken)
{
	if (is_special_env_name(*subtoken))
		return (false);
	while (*subtoken && is_valid_env_name(*subtoken))
		subtoken++;
	return (*subtoken == '\0');
}

int	count_params_size(t_subtoken_node *params)
{
	int	export_envp_size;

	export_envp_size = 0;
	while (params)
	{
		if (!validate_env_name(params->subtoken))
			break ;
		if (getenv(params->subtoken) == NULL)
			export_envp_size++;
		params = params->next;
	}
	return (export_envp_size);
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
