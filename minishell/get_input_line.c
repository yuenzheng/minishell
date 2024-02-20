/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:39:08 by ychng             #+#    #+#             */
/*   Updated: 2024/02/20 19:49:28 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*readline_until_has_character(void)
{
	char	*current_input;

	while (1)
	{
		current_input = readline("main> ");
		if (!current_input)
		{
			printf("Ctrl+D was pressed\n");
			exit(-1);
		}
		if (*current_input)
			break ;
		free(current_input);
	}
	return (current_input);
}

static bool	has_open_quote(char *final_input)
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
static char	*custom_strjoin(char *final_input, char *current_input)
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

static char	*readline_until_no_open_quote(char *input)
{
	char	*final_input;
	char	*current_input;

	final_input = input;
	while (has_open_quote(final_input))
	{
		current_input = readline("join> ");
		if (!current_input)
		{
			printf("Ctrl+D was pressed\n");
			free(final_input);
			exit(-1);
		}
		final_input = custom_strjoin(final_input, current_input);
		free(current_input);
	}
	return (final_input);
}

char	*get_input_line(void)
{
	char	*input;

	input = readline_until_has_character();
	input = readline_until_no_open_quote(input);
	return (input);
}
