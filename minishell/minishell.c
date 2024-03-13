/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:56:25 by ychng             #+#    #+#             */
/*   Updated: 2024/03/14 01:47:23 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_list(t_token_list *token_list)
{
	t_token_node	*current_tok;
	t_subtoken_node	*current_sub;

	current_tok = token_list->head;
	while (current_tok)
	{
		current_sub = current_tok->subtoken_list->head;
		while (current_sub)
		{
			printf("%s\n", current_sub->subtoken);
			current_sub = current_sub->next;
		}
		printf("\n");
		current_tok = current_tok->next;
	}
}

int	main(void)
{
	char			*input;
	t_token_list	*token_list;

	while (1)
	{
		input = get_input_line();
		token_list = get_token_list(input);
		// token_list = infix_to_postfix(token_list);
		print_list(token_list);
		free(input);
		free_token_list(token_list);
	}
}
