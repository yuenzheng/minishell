/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_user_input_utils_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:14:58 by ychng             #+#    #+#             */
/*   Updated: 2024/03/22 19:38:02 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_open_delim(char current_char)
{
	return (is_quote_char(current_char) || is_leftbracket_char(current_char));
}

bool	is_nested_delim(char current_char)
{
	return (is_leftbracket_char(current_char));
}

bool	is_close_delim(char current_char, char open_delim)
{
	if (open_delim == '\'' && current_char == '\'')
		return (true);
	else if (open_delim == '\"' && current_char == '\"')
		return (true);
	else if (open_delim == '`' && current_char == '`')
		return (true);
	else if (open_delim == '(' && current_char == ')')
		return (true);
	else if (open_delim == '[' && current_char == ']')
		return (true);
	else if (open_delim == '{' && current_char == '}')
		return (true);
	return (false);
}

bool	is_escaped_char(char current_char, char next_char, char open_delim)
{
	return (open_delim != '\'' && current_char == '\\' && next_char != '\0');
}
