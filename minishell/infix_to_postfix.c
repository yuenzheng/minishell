/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infix_to_postfix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:51:28 by ychng             #+#    #+#             */
/*   Updated: 2024/03/27 01:13:29 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	process_infix(t_tokenlist *infix, t_tokenlist *postfix, \
			t_tokenlist *opstack)
{
	while (infix->head)
	{
		if (is_leftbracket(*first_subtoken(infix->head)))
			link_tokenlist(pop_tokenlist_head(infix), opstack);
		else if (is_rightbracket(*first_subtoken(infix->head)))
		{
			while (opstack->tail && \
					!is_leftbracket(*first_subtoken(opstack->tail)))
				link_tokenlist(pop_tokenlist_tail(opstack), postfix);
			free_tokennode(pop_tokenlist_head(infix));
			free_tokennode(pop_tokenlist_tail(opstack));
		}
		else if (is_logicalop(first_subtoken(infix->head)))
		{
			while (opstack->tail && \
					priority(opstack->tail) >= priority(infix->head))
				link_tokenlist(pop_tokenlist_tail(opstack), postfix);
			link_tokenlist(pop_tokenlist_head(infix), opstack);
		}
		else
			link_tokenlist(pop_tokenlist_head(infix), postfix);
	}
}

static void	empty_opstack(t_tokenlist *opstack, t_tokenlist *postfix)
{
	while (opstack->tail)
		link_tokenlist(pop_tokenlist_tail(opstack), postfix);
}

t_tokenlist	*infix_to_postfix(t_tokenlist *infix)
{
	t_tokenlist	*postfix;
	t_tokenlist	*opstack;

	postfix = create_tokenlist();
	opstack = create_tokenlist();
	process_infix(infix, postfix, opstack);
	empty_opstack(opstack, postfix);
	free(infix);
	free(opstack);
	return (postfix);
}
