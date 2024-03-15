/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:15:48 by ychng             #+#    #+#             */
/*   Updated: 2024/03/15 16:38:39 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_subtoken_list	*update_params_list(t_subtoken_node *params, \
							t_subtoken_list *params_list)
{
	if (params_list == NULL)
		params_list = create_params_list();
	link_subtoken_list(params, params_list);
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

static char	**update_envp(char **envp, t_subtoken_node *params)
{
	t_subtoken_node	*valid_params;
	char			**valid_envp;

	valid_params = filter_params(params);
	valid_envp = create_valid_envp(envp, valid_params);
	copy_to_dest(valid_envp, envp, valid_params);
	free_subtoken_node(valid_params);
	free_envp(envp);
	return (valid_envp);
}

// My export works on static to store the all args that you have used
// It also ignored empty string, so that is easier to implement unset
// Remeber to pass a static to params_list before the call
void	blt_export(char ***envp, t_subtoken_node *params, \
			t_subtoken_list *params_list)
{
	char	**export_envp;

	params_list = update_params_list(params, params_list);
	export_envp = create_export_envp(*envp, params_list);
	if (params == NULL)
		print_export_envp(export_envp);
	free_envp(export_envp);
	if (params != NULL)
		*envp = update_envp(*envp, params);
	exit(0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	**temp;

// 	temp = envp;
// 	envp = malloc(sizeof(char *) * (count_envp_size(envp) + 1));
// 	from_envp(envp, temp);

// 	t_subtoken_node	first;
// 	t_subtoken_node	second;
// 	t_subtoken_node	third;
// 	t_subtoken_node	fourth;
// 	t_subtoken_node	fifth;

// 	first.next = &second;
// 	second.next = &third;
// 	third.next = NULL;
// 	fourth.next = &fifth;;
// 	fifth.next = NULL;

// 	first.subtoken = "hi";
// 	second.subtoken = "bye";
// 	third.subtoken = "=";
// 	fourth.subtoken = "ABC=";
// 	fifth.subtoken = "NAME=MAX";

// 	blt_export(&envp, &first);
// 	blt_export(&envp, &fourth);

// 	int	i;

// 	i = -1;
// 	while (envp[++i])
// 		printf("%s\n",envp[i]);
// 	free_envp(envp);
// }