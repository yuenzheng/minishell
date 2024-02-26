/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:39:19 by ychng             #+#    #+#             */
/*   Updated: 2024/02/26 17:58:50 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*find_cmd_end(char *remaining_input)
{
	bool	escaped;
	bool	in_quote;
	char	quote_type;

	escaped = false;
	in_quote = false;
	quote_type = '\0';
	while (*remaining_input)
	{
		if (!escaped && !is_single_quote(quote_type)
			&& is_backslash(*remaining_input))
			escaped = true;
		else if (!escaped && is_quote(*remaining_input))
			toggle_in_quote(*remaining_input, &in_quote, &quote_type);
		else if (!escaped && !in_quote && is_logical_operator(*remaining_input))
			break ;
		else
			escaped = false;
		remaining_input++;
	}
	return (remaining_input);
}

static char	*find_logical_operator_end(char remaining_input)
{
	if (ft_strncmp(remaining_input, "|&", 2) == 0
	|| (ft_strncmp(remaining_input, "||", 2) == 0)
	|| (ft_strncmp(remaining_input, "&&", 2) == 0))
		remaining_input += 2;
	else if (ft_strncmp(remaining_input, "|", 1) == 0)
		remaining_input++;
	return (remaining_input);
}

static char	*duplicate_token(char *token, char *remaining_input)
{
	int	len;

	len = ft_strlen(token) - ft_strlen(remaining_input);
	return (ft_strndup(token, len));
}

char	*get_next_token(char *input)
{
	static char	*remaining_input;
	char		*token;

	if (input != NULL)
		remaining_input = input;
	if (!remaining_input || *remaining_input == '\0')
		return (NULL);
	token = remaining_input;
	remaining_input = find_cmd_end(remaining_input);
	if (token == remaining_input)
		remaining_input = find_logical_operator_end(remaining_input);
	return (duplicate_token(token, remaining_input));
}