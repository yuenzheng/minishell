/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_line_utils_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:11:50 by ychng             #+#    #+#             */
/*   Updated: 2024/03/24 06:20:47 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	has_openquote(char *input)
{
	bool	escaped;
	bool	inquote;
	char	quote_t;

	escaped = false;
	inquote = false;
	quote_t = '\0';
	while (*input)
	{
		if (escaped == false)
		{
			if ((is_singlequote(quote_t) == false) && is_backslash(*input))
				escaped = true;
			else if (is_quote(*input))
				toggle_inquote(*input, &inquote, &quote_t);
		}
		else
			escaped = false;
		input++;
	}
	return (inquote);
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

bool	has_openbracket(char *input)
{
	bool	escaped;
	bool	inquote;
	char	quote_t;
	int		open_count;

	escaped = false;
	inquote = false;
	quote_t = '\0';
	open_count = 0;
	while (*input)
	{
		if (escaped == false)
		{
			if ((is_singlequote(quote_t) == false) && is_backslash(*input))
				escaped = true;
			else if (is_quote(*input))
				toggle_inquote(*input, &inquote, &quote_t);
			else if (is_bracket(*input) && inquote == false)
				open_count += update_open_count(*input);
		}
		else
			escaped = false;
		input++;
	}
	return (open_count != 0);
}
