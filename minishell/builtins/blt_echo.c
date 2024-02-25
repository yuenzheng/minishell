/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:02:22 by ychng             #+#    #+#             */
/*   Updated: 2024/02/25 18:36:04 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_tokens(t_token_node *params)
{
	print_first_token(params);
	print_rest_of_tokens(params);
}

static bool	n_option_present(char *token)
{
	return (token != skip_n_options(token));
}

int	blt_echo(t_token_node *params)
{
	if (params == NULL)
	{
		printf("\n");
		return (0);
	}
	print_tokens(params);
	if (!n_option_present(params->token))
		printf("\n");
	return (0);
}

// int main()
// {
// 	t_token_node	first;
// 	t_token_node	second;
// 	t_token_node	third;

// 	first.next = &second;
// 	second.next = &third;
// 	third.next = NULL;

// 	first.token = "-nna -nnna";
// 	second.token = "-nnnnnn ya,";
// 	third.token = "so what";
// 	blt_echo(NULL);
// }