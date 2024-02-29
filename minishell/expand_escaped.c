/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_escaped.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:47:42 by ychng             #+#    #+#             */
/*   Updated: 2024/02/29 17:09:14 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	count_expanded_escaped_len(char *subtoken)
{
	int			len;
	bool		escaped;
	bool		in_quote;
	char		quote_type;

	len = 0;
	escaped = false;
	in_quote = false;
	quote_type = '\0';
	while (*subtoken)
	{
		if (!escaped && should_escape(quote_type, subtoken))
		{
			escaped = true;
			subtoken++;
			continue ;
		}
		else if (!escaped && is_quote(*subtoken))
			toggle_in_quote(*subtoken, &in_quote, &quote_type);
		else
			escaped = false;
		len++;
		subtoken++;
	}
	return (len);
}

static void	expand_escaped_chars(char *result, char *subtoken)
{
	bool		escaped;
	bool		in_quote;
	char		quote_type;

	escaped = false;
	in_quote = false;
	quote_type = '\0';
	while (*subtoken)
	{
		if (!escaped && should_escape(quote_type, subtoken))
		{
			escaped = true;
			subtoken++;
			continue ;
		}
		else if (!escaped && is_quote(*subtoken))
			toggle_in_quote(*subtoken, &in_quote, &quote_type);
		else
			escaped = false;
		*result++ = *subtoken++;
	}
	*result = '\0';
}

char	*expand_escaped(char *subtoken)
{
	char	*result;
	int		expanded_len;

	expanded_len = count_expanded_escaped_len(subtoken);
	result = malloc(sizeof(char) * (expanded_len + 1));
	if (!result)
	{
		printf("malloc failed for result\n");
		exit(-1);
	}
	expand_escaped_chars(result, subtoken);
	free(subtoken);
	return (result);
}
