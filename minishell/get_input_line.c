/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:39:08 by ychng             #+#    #+#             */
/*   Updated: 2024/03/27 01:17:58 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*closequotes(char *input)
{
	char	*joininput;

	if (has_openquotes(input))
		input = custom_strjoin(input, "\n");
	while (has_openquotes(input))
	{
		joininput = readline("join> ");
		if (!joininput)
		{
			printf("Ctrl+D was pressed in closequotes\n");
			free(input);
			exit(-1);
		}
		joininput = format_joininput(joininput);
		input = custom_strjoin(input, joininput);
		free(joininput);
	}
	return (input);
}

static char	*closebrackets(char *input)
{
	char	*joininput;
	char	*triminput;

	// while (has_openbrackets(input) == true)
	// {
		// if (empty_bracket(input))
		// 	break ;
		joininput = readline("join> ");
		if (joininput == NULL)
		{
			printf("Ctrl+D was pressed in closebrackets\n");
			free(input);
			exit(-1);
		}
		triminput = ft_strtrim(input, "\n");
		free(input);
		input = triminput;
		if (*joininput != '\0')
			input = custom_strjoin(input, " ");
		input = custom_strjoin(input, joininput);
		input = closequotes(input);
		free(joininput);
		// if (empty_bracket(input))
			// break ;
	// }
	return (input);
}

static char	*closelogicalops(char *input)
{
	char	*joininput;

	while (has_openlogicalops(input) == true)
	{
		joininput = readline("join> ");
		if (joininput == false)
		{
			printf("Ctrl+D was pressed in closelogicalops\n");
			free(input);
			exit(-1);
		}
		input = custom_strjoin(input, " ");
		input = custom_strjoin(input, joininput);
		free(joininput);
	}
	return (input);
}

char	*handle_maininput(void)
{
	bool	firstiter;
	char	*maininput;

	firstiter = true;
	maininput = NULL;
	while (firstiter || *maininput == '\0')
	{
		free(maininput);
		firstiter = false;
		maininput = readline("main> ");
		if (maininput == NULL)
		{
			printf("Ctrl+D was pressed in handle_maininput\n");
			exit(-1);
		}
	}
	return (maininput);
}

bool	has_logicaloperr(char *token, int *openlogicalops)
{
	if (is_logicalop(token) == true)
	{
		(*openlogicalops)++;
		if (*openlogicalops > 0)
		{
			printf(
				"syntax error near unexpected token `%c%c'\n", \
				token[0], token[1]);
			return (true);
		}
	}
	else if (ft_strspn(token, " ") != ft_strlen(token))
		(*openlogicalops)--;
	return (false);
}

// bool	is_empty(char *start, char *token)
// {
// 	while (token >= start)
// 	{
// 		if (is_leftbracket(*token))
// 			return (true);
// 		if (!is_space(*token) && !is_rightbracket(*token))
// 			return (false);
// 		token--;
// 	}
// 	return (true);
// }

bool	has_bracketerr(char *token, int *openbrackets)
{
	char	*start;

	token += ft_strspn(token, " ");
	start = token;
	while (*token)
	{
		if (((start == token) || *openbrackets > 0) && is_leftbracket(*token))
			(*openbrackets)++;
		else if (((start != token) && *openbrackets > 0) && is_rightbracket(*token))
			(*openbrackets)--;
		else if (((start == token) && is_rightbracket(*token)) \
			|| ((start != token) && is_bracket(*token)))
		{
			printf("syntax error near unexpected token `%c'\n", *token);
			return (true);
		}
		token++;
	}
	return (false);
}

bool	has_no_error(char *input)
{
	int		openlogicalops;
	int		openbrackets;
	char	*token;

	openlogicalops = 0;
	openbrackets = 0;
	token = get_next_token(input, false);
	while (token)
	{
		if (has_logicaloperr(token, &openlogicalops) \
			|| has_bracketerr(token, &openbrackets))
			return (false);
		free(token);
		token = get_next_token(NULL, false);
	}
	free(token);
	return (true);
}

// order don't matter
bool	has_openblock(char *input)
{
	return (has_openquotes(input) \
		|| (has_openbrackets(input)) \
		|| (has_openlogicalops(input)));
}

char	*get_input_line(void)
{
	char	*input;

	input = handle_maininput();
	while (has_no_error(input) && has_openblock(input))
	{
		input = closequotes(input);
		input = closebrackets(input);
		input = closelogicalops(input);
	}
	// printf("%s\n", input);
	return (input);
}
