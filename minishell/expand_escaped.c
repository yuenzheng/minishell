/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_escaped.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:47:42 by ychng             #+#    #+#             */
/*   Updated: 2024/02/23 20:53:08 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	count_expanded_escaped_len(char *token)
{
	int			len;
	bool		escaped;
	bool		in_quote;
	char		quote_type;

	len = 0;
	escaped = false;
	in_quote = false;
	quote_type = '\0';
	while (*token)
	{
		if (!escaped && should_escape(quote_type, token))
		{
			escaped = true;
			token++;
			continue ;
		}
		else if (!escaped && is_quote(*token))
			toggle_in_quote(*token, &in_quote, &quote_type);
		else
			escaped = false;
		len++;
		token++;
	}
	return (len);
}

static void	expand_escaped_chars(char *result, char *token)
{
	bool		escaped;
	bool		in_quote;
	char		quote_type;

	escaped = false;
	in_quote = false;
	quote_type = '\0';
	while (*token)
	{
		if (!escaped && should_escape(quote_type, token))
		{
			escaped = true;
			token++;
			continue ;
		}
		else if (!escaped && is_quote(*token))
			toggle_in_quote(*token, &in_quote, &quote_type);
		else
			escaped = false;
		*result++ = *token++;
	}
}

char	*expand_escaped(char *token)
{
	char	*result;
	int		expanded_len;

	expanded_len = count_expanded_escaped_len(token);
	result = malloc(sizeof(char) * (expanded_len + 1));
	if (!result)
	{
		printf("malloc failed for result\n");
		exit(-1);
	}
	expand_escaped_chars(result, token);
	return (result);
}
