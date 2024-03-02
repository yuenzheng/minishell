/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 01:49:09 by ychng             #+#    #+#             */
/*   Updated: 2024/03/03 02:58:26 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// I'm using the normal ft_strtok here,
// Because the subtoken would have already been expanded
// " 12"10 would just be 1210
static int	count_exit_args(t_subtoken_node *params)
{
	int		args_count;
	char	*dup_subtoken;
	char	*subtoken;

	args_count = 0;
	while (params)
	{
		dup_subtoken = ft_strdup(params->subtoken);
		subtoken = ft_strtok(dup_subtoken, " ");
		while (subtoken)
		{
			args_count++;
			subtoken = ft_strtok(NULL, " ");
		}
		free(dup_subtoken);
		params = params->next;
	}
	return (args_count);
}

// Remember to set exit_code to 1, when print("too many arguments")
// in the first if condition, that contain only numbers.
// Because it doesn't exit the function
static void	process_exit_args(t_subtoken_node *params)
{
	int		args_count;
	char	*dup_subtoken;
	char	*first_arg;

	args_count = count_exit_args(params);
	dup_subtoken = ft_strdup(params->subtoken);
	first_arg = ft_strtok(dup_subtoken, " ");
	if (first_arg && contain_only_digits(first_arg))
	{
		if (args_count == 1)
			handle_numeric_exit(first_arg, dup_subtoken);
		printf("too many arguments\n");
	}
	else
		handle_non_numeric_exit(dup_subtoken);
	free(dup_subtoken);
}

void	blt_exit(t_subtoken_node *params)
{
	if (params == NULL || count_exit_args(params) == 0)
		exit(0);
	process_exit_args(params);
}
