/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:39:01 by ychng             #+#    #+#             */
/*   Updated: 2024/03/07 02:49:39 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_subtoken_node	*filter_params(t_subtoken_node *params)
{
	t_subtoken_node	*subtoken_node;
	t_subtoken_list	valid_params_list;

	valid_params_list = (t_subtoken_list){0};		
	while (params)
	{
		if (ft_strchr(params->subtoken, '='))
		{
			subtoken_node = create_subtoken_node(params->subtoken);
			link_subtoken_node(subtoken_node, &valid_params_list);
		}
		params = params->next;
	}
	return (valid_params_list.head);
}

char	**create_envp_copy(char **envp, t_subtoken_node *valid_params)
{
	int		envp_size;
	int		params_size;
	char	**envp_copy;

	envp_size = count_envp_size(envp);
	params_size = count_params_size(valid_params);
	envp_copy = malloc(sizeof(char *) * (envp_size + params_size + 1));
	if (!envp_copy)
	{
		printf("malloc failed for envp_copy\n");
		exit(-1);
	}
	return (envp_copy);
}

void	print_export_envp(char **export_envp)
{
	char	*entry_copy;
	char	*name;
	char	*value;

	while (*export_envp)
	{
		if (is_underscore(**export_envp) && *(*export_envp + 1) == ' ')
		{
			export_envp++;
			continue ;
		}
		entry_copy = ft_strdup(*export_envp);
		name = ft_strtrim(ft_strtok(entry_copy, "="), " ");
		value = ft_strchr(*export_envp, '=');
		if (value)
		{
			value++;
			printf("declare -x %s=\"%s\"\n", name, value);
		}
		else
			printf("declare -x %s\n", name);
		free(entry_copy);
		free(name);
		export_envp++;
	}
}

void	free_export_envp(char **export_envp)
{
	int	i;

	i = -1;
	while (export_envp[++i])
		free(export_envp[i]);
	free(export_envp);
}
