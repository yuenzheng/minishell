/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_line_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:11:50 by ychng             #+#    #+#             */
/*   Updated: 2024/02/21 20:12:36 by ychng            ###   ########.fr       */
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

// The result string has to be null-terminated
// if not the first while loop in ft_strcat()
// will run with garbage value
// which will cause unexpected result
char	*custom_strjoin(char *final_input, char *current_input)
{
	int		joined_len;
	char	*result;

	if (*current_input == '\0')
		current_input = " ";
	joined_len = ft_strlen(final_input) + ft_strlen(current_input);
	result = malloc(sizeof(char) * (joined_len + 1));
	if (!result)
	{
		printf("malloc failed for result\n");
		exit(1);
	}
	*result = '\0';
	ft_strcpy(result, final_input);
	ft_strcat(result, current_input);
	free(final_input);
	return (result);
}
