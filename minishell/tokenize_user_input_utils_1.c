/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_user_input_utils_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:14:58 by ychng             #+#    #+#             */
/*   Updated: 2024/02/01 16:26:00 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	can_be_nested_char(char current_char, char next_char)
{
	return (current_char == '$' && next_char == '(');
}

bool	is_quote_char(char current_char)
{
	return (
		current_char == '\'' || current_char == '\"' || current_char == '`');
}

bool	is_open_char(char current_char, char next_char)
{
	return (can_be_nested_char(current_char, next_char)
		|| is_quote_char(current_char));
}

bool	is_matching_close_char(char current_char, char open_char)
{
	if (open_char == '\'' && current_char == '\'')
		return (true);
	else if (open_char == '\"' && current_char == '\"')
		return (true);
	else if (open_char == '`' && current_char == '`')
		return (true);
	else if (open_char == '$' && current_char == ')')
		return (true);
	return (false);
}

// Haven't set for $()
bool	is_escape_char(char current_char, char next_char)
{
	bool	next_is_escapable_char;

	next_is_escapable_char = (is_quote_char(next_char) || ')');
	return (current_char == '\\' && next_is_escapable_char);
}
