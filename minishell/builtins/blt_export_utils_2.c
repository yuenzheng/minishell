/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:39:01 by ychng             #+#    #+#             */
/*   Updated: 2024/03/07 06:55:04 by ychng            ###   ########.fr       */
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
		if (validate_entry_name(params->subtoken) && ft_strchr(params->subtoken, '='))
		{
			subtoken_node = create_subtoken_node(ft_strdup(params->subtoken));
			link_subtoken_node(subtoken_node, &valid_params_list);
		}
		params = params->next;
	}
	return (valid_params_list.head);
}

char	**create_valid_envp(char **envp, t_subtoken_node *valid_params)
{
	int		envp_size;
	int		params_size;
	char	**valid_envp;

	envp_size = count_envp_size(envp);
	params_size = count_params_size(valid_params);
	valid_envp = malloc(sizeof(char *) * (envp_size + params_size + 1));
	if (!valid_envp)
	{
		printf("malloc failed for valid_envp\n");
		exit(-1);
	}
	return (valid_envp);
}

// else if (name), is for unset
// so that if I change the subtoken to an empty str
// it will not print anything
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
		else if (name)
			printf("declare -x %s\n", name);
		free(entry_copy);
		free(name);
		export_envp++;
	}
}

void	free_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
}
