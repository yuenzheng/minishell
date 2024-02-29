/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_list_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:27:06 by ychng             #+#    #+#             */
/*   Updated: 2024/02/29 11:27:32 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_subtoken_list	*create_subtoken_list(void)
{
	t_token_list	*subtoken_list;

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
