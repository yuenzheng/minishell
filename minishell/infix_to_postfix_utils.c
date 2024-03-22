/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infix_to_postfix_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:34:51 by ychng             #+#    #+#             */
/*   Updated: 2024/03/23 01:05:45 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*first_subtoken(t_tokennode *currtok)
{
	t_subtokennode	*currsub;

	currsub = currtok->subtokenlist->head;
	return (currsub->subtoken);
}

int	priority(t_tokennode *currtok)
{
	char	*subtoken;

	subtoken = first_subtoken(currtok);
	if (ft_strcmp(subtoken, "&&") == 0)
		return (2);
	if (ft_strcmp(subtoken, "||") == 0)
		return (1);
	return (-1);
}
