/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_user_input_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:18:23 by ychng             #+#    #+#             */
/*   Updated: 2024/02/01 16:19:43 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	complete_nesting_section(int *nesting_level, char *open_char)
{
	if (*nesting_level == 0)
		*open_char = '\0';
	else if (*nesting_level > 0)
		(*nesting_level)--;
}

void	process_non_whitespace_char(
	char *user_input, char *open_char, int *nesting_level, int *i)
{
	if (!(*open_char) && is_open_char(user_input[*i], user_input[*i + 1]))
		*open_char = user_input[*i];
	else if (*open_char == '$' && can_be_nested_char(
			user_input[*i], user_input[*i + 1]))
		(*nesting_level)++;
	else if (*open_char && is_matching_close_char(user_input[*i], *open_char))
		complete_nesting_section(nesting_level, open_char);
	else if (is_escape_char(user_input[*i], user_input[*i + 1]))
		(*i)++;
	(*i)++;
}
