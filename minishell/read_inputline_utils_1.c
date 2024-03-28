/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 01:20:16 by ychng             #+#    #+#             */
/*   Updated: 2024/03/28 23:45:36 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	has_openquotes(char *input)
{
	bool	escaped;
	bool	inquote;
	char	quote_t;

	escaped = false;
	inquote = false;
	quote_t = '\0';
	while (*input)
	{
		if (!escaped && !is_singlequote(quote_t) && is_backslash(*input))
			escaped = true;
		else if (!escaped && is_quote(*input))
			toggle_inquote(*input, &inquote, &quote_t);
		else if (escaped)
			escaped = false;
		input++;
	}
	return (inquote);
}

bool	has_openbrackets(char *input)
{
	char	*start;
	bool	escaped;
	bool	inquote;
	char	quote_t;
	int		open_count;

	start = input;
	escaped = false;
	inquote = false;
	quote_t = '\0';
	open_count = 0;
	while (*input)
	{
		if (!escaped && !is_singlequote(quote_t) && is_backslash(*input))
			escaped = true;
		else if (!escaped && is_quote(*input))
			toggle_inquote(*input, &inquote, &quote_t);
		else if (!escaped && !inquote && is_bracket(*input) \
				&& (open_count || is_validpos(start, input)))
			open_count += update_open_count(*input);
		else if (escaped)
			escaped = false;
		input++;
	}
	return (open_count > 0);
}

bool	has_openlogicalops(char *input)
{
	bool	escaped;
	bool	inquote;
	char	quote_t;
	bool	inoperator;

	escaped = false;
	inquote = false;
	quote_t = '\0';
	inoperator = false;
	while (*input)
	{			
		if (!escaped && !is_singlequote(quote_t) && is_backslash(*input))
			escaped = true;
		else if (!escaped && is_quote(*input))
			toggle_inquote(*input, &inquote, &quote_t);
		else if (!escaped && !inquote && !inoperator && is_logicalop_n(input))
			input += set_inoperator_true(&inoperator);
		else if (!escaped && inoperator && !is_space(*input))
			inoperator = false;
		else if (escaped)
			escaped = false;
		input++;
	}
	return (inoperator);
}

char	*format_joininput(char *joininput)
{
	if (*joininput == '\0')
	{
		free(joininput);
		return (ft_strdup("\n"));
	}
	return (joininput);
}

bool	empty_bracket(char *input)
{
	char	*innermost_adr;
	int		i;

	innermost_adr = ft_rstrchr(input, ')');
	if (innermost_adr == NULL)
		return (false);
	i = innermost_adr - input;
	while (--i > 0)
	{
		if (is_leftbracket(input[i]) || !is_space(input[i]))
			break ;
	}
	if (is_leftbracket(input[i]))
	{
		printf("syntax error near unexpected token `)'\n");
		return (true);
	}
	return (false);
}
