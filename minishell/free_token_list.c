/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:49:34 by ychng             #+#    #+#             */
/*   Updated: 2024/02/29 11:23:59 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	free_subtoken_node(t_subtoken_node *subtoken_node)
{
	if (subtoken_node == NULL)
		return ;
	free_subtoken_node(subtoken_node->next);
	free(subtoken_node);
}

static void	free_subtoken_list(t_subtoken_list *subtoken_list)
{
	if (subtoken_list == NULL)
		return ;
	free_subtoken_node(subtoken_list->head);
	free(subtoken_list);
}

static void	free_token_node(t_token_node *token_node)
{
	if (token_node == NULL)
		return ;
	free_token_node(token_node->next);
	free_subtoken_list(token_node->subtoken_list);
	free(token_node);
}

void	free_token_list(t_token_list *token_list)
{
	if (token_list == NULL)
		return ;
	free_token_node(token_list->head);
	free(token_list);
}
