/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:06:38 by ychng             #+#    #+#             */
/*   Updated: 2024/02/27 15:28:06 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_token_node	*create_token_node(t_subtoken_node *subtoken_list)
{
	t_token_node	*token_node;

	token_node = malloc(sizeof(t_token_node));
	if (!token_node)
	{
		printf("malloc failed for token_node\n");
		exit(-1);
	}
	token_node->subtoken_list = subtoken_list;
	token_node->next = NULL;
	return (token_node);
}

void	link_token_list(t_token_node *token_list, t_token_node *token_node)
{
	t_token_node	*temp;

	if (token_list == NULL)
	{
		token_list = token_node;
		temp = token_node;
	}
	else
	{
		temp->next = token_node;
		temp = token_node;
	}
}