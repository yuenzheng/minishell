/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:02:22 by ychng             #+#    #+#             */
/*   Updated: 2024/03/17 02:29:45 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_subtokens(t_subtoken_node *params)
{
	params = find_first_non_option(params);
	while (params)
	{
		printf("%s", params->subtoken);
		if (params->next != NULL)
			printf(" ");
		params = params->next;
	}
}

static void	print_newline(t_subtoken_node *params)
{
	t_subtoken_node	*first_non_option;

	first_non_option = find_first_non_option(params);
	if (first_non_option == params)
		printf("\n");
}

int	blt_echo(t_subtoken_node *params)
{
	if (params == NULL)
	{
		printf("\n");
		return (0);
	}
	print_subtokens(params);
	print_newline(params);
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