/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_user_input_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:18:23 by ychng             #+#    #+#             */
/*   Updated: 2024/02/09 17:18:36 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	handle_open_delim_closure(char *open_delim, int *nesting_lvl)
{
	if (*nesting_lvl == 0)
		*open_delim = '\0';
	else if (*nesting_lvl > 0)
		(*nesting_lvl)--;
}

// condition for the nested condition
// only if open delimiter has a value
// and is not a quote
// then check if its nested delimiter
void	process_char_in_token(
	char current_char,
	char *open_delim,
	int *nesting_lvl,
	int *i
)
{
	if (!(*open_delim) && is_open_delim(current_char))
		*open_delim = current_char;
	else if (*open_delim && !is_quote_char(*open_delim)
		&& is_nested_delim(current_char))
		(*nesting_lvl)++;
	else if (is_close_delim(current_char, *open_delim))
		handle_open_delim_closure(open_delim, nesting_lvl);
	else if (is_escaped_char(current_char, *open_delim))
		(*i)++;
	(*i)++;
}
