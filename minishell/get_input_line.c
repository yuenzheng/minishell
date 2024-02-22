/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:39:08 by ychng             #+#    #+#             */
/*   Updated: 2024/02/22 19:55:25 by ychng            ###   ########.fr       */
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

static char	*readline_until_no_open_quote(char *input)
{
	char	*final_input;
	char	*temp_input;
	char	*current_input;

	final_input = input;
	while (has_open_quote(final_input))
	{
		temp_input = readline("join> ");
		if (!temp_input)
		{
			printf("Ctrl+D was pressed\n");
			free(final_input);
			exit(-1);
		}
		current_input = normalize_input(temp_input);
		final_input = custom_strjoin(final_input, current_input);
		if (current_input == temp_input)
			free(current_input);
	}
	return (final_input);
}

static void	add_input_to_history(char *input)
{
	static char	*previous_input;

	if (previous_input && ft_strcmp(previous_input, input) == 0
		&& !contains_newline(input))
		return ;
	if (previous_input != NULL)
		free(previous_input);
	previous_input = ft_strdup(input);
	if (!previous_input)
	{
		printf("ft_strdup failed for previous_input\n");
		exit(-1);
	}
	add_history(previous_input);
}

char	*get_input_line(void)
{
	char	*input;

	input = readline_until_has_character();
	input = readline_until_no_open_quote(input);
	add_input_to_history(input);
	return (input);
}
