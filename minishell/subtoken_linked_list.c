/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtoken_linked_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:25:10 by ychng             #+#    #+#             */
/*   Updated: 2024/02/29 11:40:19 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_subtoken_node	*create_subtoken_node(char *subtoken)
{
	t_subtoken_node	*subtoken_node;

	subtoken_node = malloc(sizeof(t_subtoken_node));
	if (!subtoken_node)
	{
		printf("malloc failed for subtoken_node\n");
		exit(-1);
	}
	subtoken_node->subtoken = subtoken;
	subtoken_node->next = NULL;
	return (subtoken_node);
}

void	link_subtoken_node(t_subtoken_node *subtoken_node, \
			t_subtoken_list *subtoken_list)
{
	if (subtoken_list->head == NULL)
	{
		subtoken_list->head = subtoken_node;
		subtoken_list->tail = subtoken_node;
	}
	else
	{
		subtoken_list->tail->next = subtoken_node;
		subtoken_list->tail = subtoken_node;
	}
}
