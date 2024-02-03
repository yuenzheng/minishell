/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_user_input_utils_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:25:44 by ychng             #+#    #+#             */
/*   Updated: 2024/02/03 18:33:12 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_whitespace_char(char character)
{
	return (character == ' ');
}

bool	is_quote_char(char character)
{
	return (character == '\'' || character == '\"' || character == '`');
}

bool	is_left_bracket_char(char character)
{
	return (character == '(' || character == '[' || character == '{');
}
