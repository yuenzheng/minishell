/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_line_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 06:09:32 by ychng             #+#    #+#             */
/*   Updated: 2024/03/25 03:05:41 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_validpos(char *start, char *input)
{
	bool	inoperator;

	inoperator = false;
	start += ft_strspn(start, " ");
	if (start == input)
		return (true);
	while (*start)
	{
		if (!inoperator && is_logical_op_n(start))
		{
			inoperator = true;
			start++;
		}
		else if (inoperator && !is_space(*start))
		{
			if (is_leftbracket(*start))
				return (true);
			break ;
		}
		start++;
	}
	return (false);
}

int	update_open_count(char c)
{
	if (is_leftbracket(c))
		return (1);
	if (is_rightbracket(c))
		return (-1);
	return (0);
}
