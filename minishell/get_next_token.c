/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:04:09 by ychng             #+#    #+#             */
/*   Updated: 2024/02/18 18:23:35 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*skip_delimeters(char *str, char *delim)
{
	return (str + ft_strspn(str, delim));
}

bool	is_backslash(char c)
{
	return (c == '\\');
}

bool	is_single_quote(char c)
{
	return (c == '\'');
}

bool	is_double_quote(char c)
{
	return (c == '\"');
}

bool	is_quote(char c)
{
	return (is_single_quote(c) || is_double_quote(c));
}

void	toggle_in_quote(char c, bool *in_quote, char *quote_type)
{
	if (*in_quote == false)
	{
		*in_quote = true;
		*quote_type = c;
	}
	else if (c == *quote_type)
	{
		*in_quote = false;
		*quote_type = '\0';
	}
}

bool	is_delim(char c, char *delim)
{
	return (ft_strchr(delim, c));
}

char	*find_token_end(char *remaining_input, char *delim)
{
	bool		escaped;
	bool		in_quote;
	char		quote_type;

	escaped = false;
	in_quote = false;
	quote_type = '\0';
	while (*remaining_input)
	{
		if (!escaped && is_backslash(*remaining_input))
			escaped = true;
		else if (!escaped && is_quote(*remaining_input))
			toggle_in_quote(*remaining_input, &in_quote, &quote_type);
		else if (!escaped && !in_quote && is_delim(*remaining_input, delim))
			break ;
		else
			escaped = false;
		remaining_input++;
	}
	return (remaining_input);
}

char	*advance_to_next_token(char *remaining_input)
{
	if (*remaining_input)
	{
		*remaining_input = '\0';
		remaining_input++;
	}
	return (remaining_input);
}

char	*get_next_token(char *input, char *delim)
{
	static char	*remaining_input;
	char		*token;

	if (input != NULL)
		remaining_input = input;
	if (*remaining_input == '\0')
		return (NULL);
	remaining_input = skip_delimeters(remaining_input, delim);
	token = remaining_input;
	remaining_input = find_token_end(remaining_input, delim);
	remaining_input = advance_to_next_token(remaining_input);
	return (token);
}

// int	main(void)
// {
// 	char	*input;
// 	char	*token;

// 	input = readline("> ");
// 	token = get_next_token(input, " ");
// 	while (token)
// 	{
// 		printf("%s\n", token);
// 		token = get_next_token(NULL, " ");
// 	}
// }