/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infix_to_postfix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:51:28 by ychng             #+#    #+#             */
/*   Updated: 2024/03/14 14:39:45 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	process_infix(t_token_list *infix, t_token_list *postfix, \
			t_token_list *opstack)
{
	while (infix->head)
	{
		if (is_left_bracket(*first_subtoken(infix->head)))
			link_token_list(pop_token_list_head(infix), opstack);
		else if (is_right_bracket(*first_subtoken(infix->head)))
		{
			while (opstack->tail && \
					!is_left_bracket(*first_subtoken(opstack->tail)))
				link_token_list(pop_token_list_tail(opstack), postfix);
			free_token_node(pop_token_list_head(infix));
			free_token_node(pop_token_list_tail(opstack));
		}
		else if (is_logical_operator(first_subtoken(infix->head)))
		{
			while (opstack->tail && \
					priority(opstack->tail) >= priority(infix->head))
				link_token_list(pop_token_list_tail(opstack), postfix);
			link_token_list(pop_token_list_head(infix), opstack);
		}
		else
			link_token_list(pop_token_list_head(infix), postfix);
	}
}

static void	empty_opstack(t_token_list *opstack, t_token_list *postfix)
{
	while (opstack->tail)
		link_token_list(pop_token_list_tail(opstack), postfix);
}

t_token_list	*infix_to_postfix(t_token_list *infix)
{
	t_token_list	*postfix;
	t_token_list	*opstack;

	postfix = create_token_list();
	opstack = create_token_list();
	process_infix(infix, postfix, opstack);
	empty_opstack(opstack, postfix);
	free(infix);
	free(opstack);
	return (postfix);
}
