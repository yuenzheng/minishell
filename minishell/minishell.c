/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:56:25 by ychng             #+#    #+#             */
/*   Updated: 2024/03/19 19:29:06 by ychng            ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_token_list	*token_list;

	((void)argc, (void)argv);
	envp = clone_envp_with_special(envp);
	while (1)
	{
		input = get_input_line();
		token_list = get_token_list(input, envp);
		token_list = infix_to_postfix(token_list);
		evaluate_postfix(&envp, token_list);
		// print_list(token_list);
		free(input);
		free_token_list(token_list);
	}
}
