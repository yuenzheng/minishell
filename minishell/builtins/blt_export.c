/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:15:48 by ychng             #+#    #+#             */
/*   Updated: 2024/03/07 03:03:40 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_subtoken_list	*update_params_list(t_subtoken_node *params, \
							t_subtoken_list *params_list)
{
	if (params_list == NULL)
		params_list = create_params_list();
	link_subtoken_node(params, params_list);
	return (params_list);
}

static char	**create_export_envp(char **envp, t_subtoken_list *params_list)
{
	char	**export_envp;

	export_envp = alloc_export_envp(envp, params_list->head);
	copy_to_dest(export_envp, envp, params_list->head);
	pad_export_envp(export_envp);
	radix_sort(export_envp);
	return (export_envp);
}

static void	update_envp(char **envp, t_subtoken_node *params)
{
	t_subtoken_node	*valid_params;
	char			**envp_copy;
	int				total_size;

	valid_params = filter_params(params);
	envp_copy = create_envp_copy(envp, valid_params);
	copy_to_dest(envp_copy, envp, valid_params);
	total_size = count_envp_size(envp) + count_params_size(valid_params);
	ft_memcpy(envp, envp_copy, sizeof(char *) * (total_size + 1));
}

int	blt_export(char **envp, t_subtoken_node *params)
{
	static t_subtoken_list	*params_list;
	char					**export_envp;

	params_list = update_params_list(params, params_list);
	export_envp = create_export_envp(envp, params_list);
	if (params == NULL)
		print_export_envp(export_envp);
	free_export_envp(export_envp);
	update_envp(envp, params);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_subtoken_node	fir;
	t_subtoken_node	sec;
	t_subtoken_node	thi;

	fir.next = &sec;
	sec.next = &thi;
	thi.next = NULL;

	fir.subtoken = "Ahithere=";
	sec.subtoken = "ya12";
	thi.subtoken = "_7=";

	blt_export(envp, &fir);
	t_subtoken_node fou;
	t_subtoken_node fiv;

	fou.next = &fiv;
	fiv.next = NULL;
	fou.subtoken = "mml";
	fiv.subtoken = "ABC";
	blt_export(envp, &fou);

	while (*envp)
	{
		printf("%s\n", *envp);
		// free(*envp);
		envp++;
	}
}
