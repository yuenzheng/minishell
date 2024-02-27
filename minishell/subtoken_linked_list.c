/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtoken_linked_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:25:10 by ychng             #+#    #+#             */
/*   Updated: 2024/02/27 15:30:45 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_subtoken_node	*create_subtoken_node(char *token)
{
	t_subtoken_node	*subtoken_node;

	subtoken_node = malloc(sizeof(t_subtoken_node));
	if (!subtoken_node)
	{
		printf("malloc failed for subtoken_node\n");
		exit(-1);
	}
	subtoken_node->token = token;
	subtoken_node->next = NULL;
	return (subtoken_node);
}

void	link_subtoken_list(t_subtoken_node *subtoken_list,
	t_subtoken_node *subtoken_node)
{
	t_subtoken_node	*temp;

	if (subtoken_list == NULL)
	{
		subtoken_list = subtoken_node;
		temp = subtoken_node;
	}
	else
	{
		temp->next = subtoken_node;
		temp = subtoken_node;
	}
}
