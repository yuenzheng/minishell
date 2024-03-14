/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_check_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:57:02 by ychng             #+#    #+#             */
/*   Updated: 2024/03/15 01:43:47 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_equal(char c)
{
	return (c == '=');
}

bool	is_left_bracket(char c)
{
	return (c == '(');
}

bool	is_right_bracket(char c)
{
	return (c == ')');
}

bool	is_bracket(char c)
{
	return (is_left_bracket(c) || is_right_bracket(c));
}

bool	is_pipe(char c)
{
	return (c == '|');
}
