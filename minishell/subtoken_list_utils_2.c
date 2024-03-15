/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtoken_list_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:19:44 by ychng             #+#    #+#             */
/*   Updated: 2024/03/15 18:20:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	count_subtoken_list(t_subtoken_list *subtoken_list)
{
	int				count;
	t_subtoken_node	*current;

	count = 0;
	current = subtoken_list->head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
