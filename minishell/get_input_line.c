/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:39:08 by ychng             #+#    #+#             */
/*   Updated: 2024/03/24 06:56:04 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*complete_quotes(char *input)
{
	char	*joininput;

	if (has_openquote(input))
		input = custom_strjoin(input, "\n");
	while (has_openquote(input))
	{
		joininput = readline("join> ");
		if (!joininput)
		{
			printf("Ctrl+D was pressed in complete_quotes\n");
			free(input);
			exit(-1);
		}
		joininput = format_joininput(joininput);
		input = custom_strjoin(input, joininput);
		free(joininput);
	}
	return (input);
}

static char	*complete_brackets(char *input)
{
	char	*joininput;
	char	*trimmed;

	while (has_openbracket(input) == true)
	{
		joininput = readline("join> ");
		if (joininput == NULL)
		{
			printf("Ctrl+D was pressed in complete_brackets\n");
			free(input);
			exit(-1);
		}
		trimmed = ft_strtrim(input, "\n");
		free(input);
		input = trimmed;
		if ((is_leftbracket(*joininput) == false) && *joininput != '\0')
			input = custom_strjoin(input, " ");
		input = custom_strjoin(input, joininput);
		input = complete_quotes(input);
		free(joininput);
	}
	return (input);
}

static char	*start_reading(void)
{
	char	*maininput;

	while (1)
	{
		maininput = readline("main> ");
		if (!maininput)
		{
			printf("Ctrl+D was pressed in start_reading\n");
			exit(-1);
		}
		if (is_leftbracket(*(maininput + ft_strspn(maininput, " "))))
		{
			maininput = complete_brackets(maininput);
			break ;
		}
		else if (*maininput != '\0')
			break ;
		free(maininput);
	}
	return (maininput);
}

static void	update_history(char *input)
{
	static char	*previnput;

	if (previnput && !ft_strcmp(previnput, input) && !contains_newline(input))
		return ;
	if (previnput != NULL)
		free(previnput);
	previnput = ft_strdup(input);
	if (!previnput)
	{
		printf("ft_strdup failed for previnput\n");
		exit(-1);
	}
	add_history(previnput);
}

char	*get_input_line(void)
{
	char	*input;

	input = start_reading();
	input = complete_quotes(input);
	// input = complete_brackets(input);
	update_history(input);
	return (input);
}
