/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:32:15 by ychng             #+#    #+#             */
/*   Updated: 2024/03/26 03:56:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	len_of_operator(char *remaining_input)
{
	if (is_bracket(*remaining_input))
		return (1);
	if (is_logical_op_n(remaining_input))
		return (2);
	return (0);
}

bool	is_bracket_or_logical_operator(char *remaining_input, bool withbracket)
{
	if (withbracket == false)
		return (is_logical_op_n(remaining_input));
	return (is_bracket(*remaining_input)
		|| (is_logical_op_n(remaining_input)));
}
