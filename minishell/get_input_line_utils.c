/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_line_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:11:50 by ychng             #+#    #+#             */
/*   Updated: 2024/02/22 20:14:28 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	has_open_quote(char *final_input)
{
	bool	escaped;
	bool	in_quote;
	char	quote_type;

	escaped = false;
	in_quote = false;
	quote_type = '\0';
	while (*final_input)
	{
		if (!escaped && is_backslash(*final_input))
			escaped = true;
		else if (!escaped && is_quote(*final_input))
			toggle_in_quote(*final_input, &in_quote, &quote_type);
		else
			escaped = false;
		final_input++;
	}
	return (in_quote);
}

char	*normalize_input(char *temp_input)
{
	if (*temp_input == '\0')
	{
		free(temp_input);
		return ("\n\n");
	}
	return (temp_input);
}
