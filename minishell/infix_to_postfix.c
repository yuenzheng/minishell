/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infix_to_postfix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:51:28 by ychng             #+#    #+#             */
/*   Updated: 2024/03/13 20:16:58 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*get_first_subtoken(t_token_node *token_node)
{
	return (token_node->subtoken_list->head->subtoken);
}

static void	process_infix(t_token_list *infix, t_token_list *postfix, \
			t_token_list *opstack)
{
	while (infix->head)
	{
		if (!is_logical_operator(get_first_subtoken(infix->head)))
			link_token_list(pop_token_list(infix), postfix);
		else if (is_logical_operator(get_first_subtoken(infix->head)))
		{
			if (opstack->head)
				link_token_list(pop_token_list(opstack), postfix);
			link_token_list(pop_token_list(infix), opstack);
		}
		else if (ft_strcmp(get_first_subtoken(infix->head), "(") == 0)
			link_token_list(pop_token_list(infix), opstack);
		else if (ft_strcmp(get_first_subtoken(infix->head), ")") == 0)
		{
			while (ft_strcmp(get_first_subtoken(opstack->head), "(") != 0)
				link_token_list(pop_token_list(opstack), postfix);
			free_token_node(pop_token_list(infix));
			free_token_node(pop_token_list(opstack));
		}
	}
}

static void	empty_opstack(t_token_list *opstack, t_token_list *postfix)
{
	int	opstack_count;

	opstack_count = count_token_list(opstack);
	while (opstack_count--)
		link_token_list(pop_token_list(opstack), postfix);
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
