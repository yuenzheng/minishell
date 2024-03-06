/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:10:05 by ychng             #+#    #+#             */
/*   Updated: 2024/03/07 01:11:53 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_subtoken_list	*create_params_list(void)
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

static char	**create_export_envp(char **envp, t_subtoken_list *params_list)
{
	int		envp_size;
	int		params_size;
	char	**export_envp;

	envp_size = count_envp_size(envp);
	params_size = count_params_size(params_list);
	export_envp = malloc(sizeof(char *) * (envp_size + params_size + 1));
	if (!export_envp)
	{
		printf("malloc failed for export_envp\n");
		exit(-1);
	}
	return (export_envp);
}

static void	copy_to_export_envp(char **export_envp, char **envp, \
				t_subtoken_list *params_list)
{
	from_envp(export_envp, envp);
	from_params(export_envp + count_envp_size(envp), params_list);
}

int	blt_export(char **envp, t_subtoken_node *params)
{
	static t_subtoken_list	*params_list;
	char					**export_envp;

	if (params_list == NULL)
		params_list = create_params_list();
	link_subtoken_node(params, params_list);
	export_envp = create_export_envp(envp, params_list);
	copy_to_export_envp(export_envp, envp, params_list);
	pad_export_envp(export_envp);
	radix_sort(export_envp);
	if (params == NULL)
		print_export_envp(export_envp);
	free_export_envp(export_envp);
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
	thi.subtoken = "_7";

	blt_export(envp, &fir);
	t_subtoken_node fou;
	t_subtoken_node fiv;

	fou.next = &fiv;
	fiv.next = NULL;
	fou.subtoken = "mml";
	fiv.subtoken = "ABC";
	blt_export(envp, &fou);
}
