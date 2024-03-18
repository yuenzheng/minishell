/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:02:22 by ychng             #+#    #+#             */
/*   Updated: 2024/03/18 22:02:25 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_subtokens(t_subtoken_node *args)
{
	args = find_first_non_option(args);
	while (args)
	{
		printf("%s", args->subtoken);
		if (args->next != NULL)
			printf(" ");
		args = args->next;
	}
}

static void	print_newline(t_subtoken_node *args)
{
	t_subtoken_node	*first_non_option;

	first_non_option = find_first_non_option(args);
	if (first_non_option == args)
		printf("\n");
}

int	blt_echo(t_subtoken_node *args)
{
	if (args == NULL)
	{
		printf("\n");
		return (0);
	}
	print_subtokens(args);
	print_newline(args);
	return (0);
}

// int main()
// {
// 	t_subtoken_node	first;
// 	t_subtoken_node	second;
// 	t_subtoken_node	third;

// 	first.next = &second;
// 	second.next = &third;
// 	third.next = NULL;

// 	first.subtoken = "-nnnnnnnnnnnn";
// 	second.subtoken = "-nnnm";
// 	third.subtoken = "so what";
// 	blt_echo(&first);
// }