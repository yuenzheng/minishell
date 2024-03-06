/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:33:57 by ychng             #+#    #+#             */
/*   Updated: 2024/03/07 02:38:37 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_subtoken_list	*create_params_list(void)
{
	t_subtoken_list	*params_list;

	params_list = malloc(sizeof(t_subtoken_list));
	if (!params_list)
	{
		printf("malloc failed for params_list\n");
		exit(-1);
	}
	params_list->head = NULL;
	params_list->tail = NULL;
	return (params_list);
}

char	**alloc_export_envp(char **envp, t_subtoken_node *params)
{
	int		envp_size;
	int		params_size;
	char	**export_envp;

	envp_size = count_envp_size(envp);
	params_size = count_params_size(params);
	export_envp = malloc(sizeof(char *) * (envp_size + params_size + 1));
	if (!export_envp)
	{
		printf("malloc failed for export_envp\n");
		exit(-1);
	}
	return (export_envp);
}

void	copy_to_dest(char **dest, char **envp, t_subtoken_node *params)
{
	from_envp(dest, envp);
	from_params(dest + count_envp_size(envp), params);
}

void	pad_export_envp(char **export_envp)
{
	int	max_len;

	max_len = get_max_name_len(export_envp);
	while (*export_envp)
	{
		*export_envp = pad_name(*export_envp, max_len);
		export_envp++;
	}
}

void	radix_sort(char **export_envp)
{
	int	pos;

	pos = get_max_name_len(export_envp);
	while (pos--)
		count_sort(export_envp, count_envp_size(export_envp), pos);
}
