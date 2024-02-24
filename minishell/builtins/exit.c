/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 01:49:09 by ychng             #+#    #+#             */
/*   Updated: 2024/02/25 16:12:42 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_exit_args(t_token_node *params)
{
	int		args_count;
	char	*dup_token;
	char	*token;

	args_count = 0;
	while (params)
	{
		dup_token = ft_strdup(params->token);
		token = ft_strtok(dup_token, " ");
		while (token)
		{
			args_count++;
			token = ft_strtok(NULL, " ");
		}
		free(dup_token);
		params = params->next;
	}
	return (args_count);
}

// Remember to set exit_code to 1, when print("too many arguments")
// in the first if condition, that contain only numbers.
// Because it doesn't exit the function
static void	process_exit_args(t_token_node *params)
{
	int		args_count;
	char	*dup_token;
	char	*first_arg;

	args_count = count_exit_args(params);
	dup_token = ft_strdup(params->token);
	first_arg = ft_strtok(dup_token, " ");
	if (first_arg && contain_only_numbers(first_arg))
	{
		if (args_count == 1)
			handle_numeric_exit(first_arg, dup_token);
		printf("too many arguments\n");
	}
	else
		handle_non_numeric_exit(dup_token);
	free(dup_token);
}

void	exit(t_token_node *params)
{
	if (params == NULL || count_exit_args(params) == 0)
		exit(0);
	process_exit_args(params);
}
