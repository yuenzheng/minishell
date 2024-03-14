/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_postfix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:33:20 by ychng             #+#    #+#             */
/*   Updated: 2024/03/14 22:54:48 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	operand_succeed(t_token_node *operand)
{
	
}

void	process_expression(t_token_list *postfix, t_token_list *stack)
{
	t_token_node	*operator;
	t_token_node	*loperand;
	t_token_node	*roperand;

	operator = pop_token_list_head(postfix);
	loperand = pop_token_list_tail(stack);
	roperand = pop_token_list_tail(stack);
	if (ft_strcmp(operator, "||") == 0)
	{
		t_token_node	*result;
		
		if (operand_succeed(loperand))
			result = loperand;
		else if (operand_succeed(roperand))
			result = roperand;
		link_token_list(result, stack);
	}
}

void	evaluate_postfix(t_token_list *postfix)
{
	t_token_list	stack;

	stack = (t_token_list){0};
	while (postfix->head)
	{
		if (is_logical_operator(first_subtoken(postfix->head)))
			process_expression(postfix, &stack);
		else
			link_token_list(pop_token_list_head(postfix), &stack);
	}
}
