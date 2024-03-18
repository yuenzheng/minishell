/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:15:48 by ychng             #+#    #+#             */
/*   Updated: 2024/03/18 22:02:25 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_subtoken_list	*update_args_history(t_subtoken_node *args, \
							t_subtoken_list *args_history)
{
	if (args_history == NULL)
		args_history = create_args_history();
	link_subtoken_list(args, args_history);
	return (args_history);
}

static char	**create_export_envp(char **envp, t_subtoken_list *args_history)
{
	char	**export_envp;

	export_envp = alloc_export_envp(envp, args_history->head);
	copy_to_dest(export_envp, envp, args_history->head);
	pad_export_envp(export_envp);
	radix_sort(export_envp);
	return (export_envp);
}

static char	**update_envp(char **envp, t_subtoken_node *args)
{
	t_subtoken_node	*valid_args;
	char			**valid_envp;

	valid_args = filter_args(args);
	valid_envp = create_valid_envp(envp, valid_args);
	copy_to_dest(valid_envp, envp, valid_args);
	free_subtoken_node(valid_args);
	free_envp(envp);
	return (valid_envp);
}

// My export works on static to store the all args that you have used
// It also ignored empty string, so that is easier to implement unset
// Remeber to pass a static to args_history before the call
int	blt_export(char ***envp, t_subtoken_node *args, \
			t_subtoken_list *args_history)
{
	char	**export_envp;

	args_history = update_args_history(args, args_history);
	export_envp = create_export_envp(*envp, args_history);
	if (args == NULL)
		print_export_envp(export_envp);
	free_envp(export_envp);
	if (args != NULL)
		*envp = update_envp(*envp, args);
	return (0);
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