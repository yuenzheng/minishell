/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:06:38 by ychng             #+#    #+#             */
/*   Updated: 2024/03/13 20:05:46 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_token_node	*create_token_node(t_subtoken_list *subtoken_list)
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

t_token_list	*create_token_list(void)
{
	t_token_list	*token_list;

	token_list = malloc(sizeof(t_token_list));
	if (!token_list)
	{
		printf("malloc failed for token_list\n");
		exit(-1);
	}
	token_list->head = NULL;
	token_list->tail = NULL;
	return (token_list);
}

t_token_node	*pop_token_list(t_token_list *token_list)
{
	t_token_node	*pop_node;
	t_token_node	*new_head;

	if (token_list == NULL || token_list->head == NULL)
		return (NULL);
	pop_node = token_list->head;
	new_head = pop_node->next;
	if (new_head == NULL)
	{
		token_list->head = NULL;
		token_list->tail = NULL;
	}
	else
	{
		pop_node->next = NULL;
		new_head->prev = NULL;
		token_list->head = new_head;
	}
	return (pop_node);
}

void	link_token_list(t_token_node *token_node, t_token_list *token_list)
{
	if (token_list->head == NULL)
	{
		token_list->head = token_node;
		token_list->tail = token_node;
	}
	else
	{
		token_list->tail->next = token_node;
		token_node->prev = token_list->tail;
		token_list->tail = token_node;
	}
}

int	count_token_list(t_token_list *token_list)
{
	int				count;
	t_token_node	*current;

	count = 0;
	current = token_list->head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
