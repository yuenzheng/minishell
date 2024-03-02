/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:02:22 by ychng             #+#    #+#             */
/*   Updated: 2024/03/03 02:28:16 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_subtokens(t_subtoken_node *params)
{
	print_first_subtoken(params);
	print_remaining_subtokens(params);
}

static bool	n_option_present(char *subtoken)
{
	return (subtoken != skip_n_options(subtoken));
}

int	blt_echo(t_subtoken_node *params)
{
	if (params == NULL)
	{
		printf("\n");
		return (0);
	}
	print_subtokens(params);
	if (!n_option_present(params->subtoken))
		printf("\n");
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

// 	first.token = "-nna -nnna";
// 	second.token = "-nnnnnn ya,";
// 	third.token = "so what";
// 	blt_echo(NULL);
// }