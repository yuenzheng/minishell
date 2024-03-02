/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_check_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:37:12 by ychng             #+#    #+#             */
/*   Updated: 2024/03/03 02:55:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_tilde(char c)
{
	return (c == '~');
}

bool	is_newline(char c)
{
	return (c == '\n');
}

bool	is_escapable(char c)
{
	return (is_backslash(c)
		|| (is_double_quote(c))
		|| (is_newline(c)));
}

bool	is_space(char c)
{
	return (c == ' ');
}

bool	is_sign(char c)
{
	return (c == '+' || c == '-');
}
