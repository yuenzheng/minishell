/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtoken_linked_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:25:10 by ychng             #+#    #+#             */
/*   Updated: 2024/03/13 19:55:31 by ychng            ###   ########.fr       */
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

t_subtoken_list	*create_subtoken_list(void)
{
	t_subtoken_list	*subtoken_list;

	subtoken_list = malloc(sizeof(t_subtoken_list));
	if (!subtoken_list)
	{
		printf("malloc failed for subtoken_list\n");
		exit(-1);
	}
	subtoken_list->head = NULL;
	subtoken_list->tail = NULL;
	return (subtoken_list);
}

void	link_subtoken_list(t_subtoken_node *subtoken_node, \
			t_subtoken_list *subtoken_list)
{
	if (subtoken_list->head == NULL)
	{
		subtoken_list->head = subtoken_node;
		subtoken_list->tail = subtoken_node;
	}
	else
	{
		while (subtoken_list->tail->next)
			subtoken_list->tail = subtoken_list->tail->next;
		subtoken_list->tail->next = subtoken_node;
		subtoken_list->tail = subtoken_node;
	}
}
