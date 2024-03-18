/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:33:57 by ychng             #+#    #+#             */
/*   Updated: 2024/03/18 22:02:25 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_subtoken_list	*create_args_history(void)
{
	t_subtoken_list	*args_history;

	args_history = malloc(sizeof(t_subtoken_list));
	if (!args_history)
	{
		printf("malloc failed for args_history\n");
		exit(-1);
	}
	args_history->head = NULL;
	args_history->tail = NULL;
	return (args_history);
}

char	**alloc_export_envp(char **envp, t_subtoken_node *args)
{
	int		envp_size;
	int		args_size;
	char	**export_envp;

	envp_size = count_envp_size(envp);
	args_size = count_args_size(args);
	export_envp = malloc(sizeof(char *) * (envp_size + args_size + 1));
	if (!export_envp)
	{
		printf("malloc failed for export_envp\n");
		exit(-1);
	}
	return (export_envp);
}

void	copy_to_dest(char **dest, char **envp, t_subtoken_node *args)
{
	from_envp(dest, envp);
	from_args(dest + count_envp_size(envp), args);
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
