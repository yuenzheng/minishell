/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infix_to_postfix_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:34:51 by ychng             #+#    #+#             */
/*   Updated: 2024/03/14 14:37:22 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*first_subtoken(t_token_node *current_tok)
{
	t_subtoken_node	*current_sub;

	current_sub = current_tok->subtoken_list->head;
	return (current_sub->subtoken);
}

int	priority(t_token_node *current_tok)
{
	char	*subtoken;

	subtoken = first_subtoken(current_tok);
	if (ft_strcmp(subtoken, "&&") == 0)
		return (2);
	if (ft_strcmp(subtoken, "||") == 0)
		return (1);
	return (-1);
}
