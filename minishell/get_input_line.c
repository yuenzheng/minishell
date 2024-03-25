/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:39:08 by ychng             #+#    #+#             */
/*   Updated: 2024/03/26 05:47:11 by ychng            ###   ########.fr       */
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

	while (has_openbrackets(input) == true)
	{
		if (empty_bracket(input))
			break ;
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
		if (empty_bracket(input))
			break ;
	}
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

bool	has_logical_error(char *token, int *logicalop_count)
{
	if (is_logical_op(token))
	{
		(*logicalop_count)++;
		if (*logicalop_count > 0)
		{
			printf("syntax error near unexpected token `%c%c'\n", \
				token[0], token[1]);
			return (true);
		}
	}
	else if (ft_strspn(token, " ") != ft_strlen(token))
		(*logicalop_count)--;
	return (false);
}

bool	has_bracket_error(char *token)
{
	char	*start;
	int		openbracket;
	int		i;

	openbracket = 0;
	i = ft_strspn(token, " ");
	start = &token[i];
	while (token[i])
	{
		if (((start == &token[i]) && is_leftbracket(token[i])) || openbracket > 0)
			openbracket++;
		else if (is_rightbracket(token[i]))
		{
			openbracket--;
			if (openbracket == -1)
			{
				printf("syntax error near unexpected token `%c'\n", token[i]);
				return (true);
			}
		}
		else if (openbracket <= 0 && is_bracket(token[i]))
		{
			printf("syntax error near unexpected token `%c'\n", token[i]);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	has_no_error(char *input)
{
	bool	flag;
	int		logicalop_count;
	char	*token;

	flag = true;
	logicalop_count = 0;
	token = get_next_token(input, false);
	while (token)
	{
		if (has_logical_error(token, &logicalop_count) \
			|| has_bracket_error(token))
		{
			flag = false;
			break ;
		}
		free(token);
		token = get_next_token(NULL, false);
	}
	free(token);
	return (flag);
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
	char		*input;

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
