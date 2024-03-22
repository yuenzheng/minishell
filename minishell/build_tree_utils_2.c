/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:41:10 by ychng             #+#    #+#             */
/*   Updated: 2024/03/23 02:48:45 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_treenode	*getlastnode(t_treenode *cmdlist)
{
	t_treenode	*tail;

	tail = cmdlist;
	while (tail->next != NULL)
		tail = tail->next;
	return (tail);
}
