/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_subtoken.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:44:03 by ychng             #+#    #+#             */
/*   Updated: 2024/02/28 12:58:24 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*find_subtoken_start(char *remaining_token)
{
	return (remaining_token + ft_strspn(remaining_token, " "));
}

static char	*find_str_subtoken_end(char *subtoken)
{
	bool	escaped;
	bool	in_quote;
	char	quote_type;

	escaped = false;
	in_quote = false;
	quote_type = '\0';
	while (*subtoken)
	{
		if (!escaped && !in_quote && is_backslash(*subtoken))
			escaped = true;
		else if (!escaped && is_quote(*subtoken))
			toggle_in_quote(*subtoken, &in_quote, &quote_type);
		else if (!escaped && !in_quote
			&& (is_space(*subtoken) || is_redirection(subtoken)))
			break ;
		else
			escaped = false;
		subtoken++;
	}
	return (subtoken);
}

static char	*find_redir_subtoken_end(char *subtoken)
{
	if (ft_strncmp(subtoken, "<<<", 3) == 0)
		subtoken += 3;
	else if (ft_strncmp(subtoken, "<<", 2) == 0
		|| ft_strncmp(subtoken, ">>", 2) == 0)
		subtoken += 2;
	else if (ft_strncmp(subtoken, "<", 1) == 0
		|| ft_strncmp(subtoken, ">", 1) == 0)
		subtoken++;
	return (subtoken);
}

static char	*duplicate_subtoken(char *subtoken, char *remaining_token)
{
	int	len;

	len = remaining_token - subtoken;
	if (len == 0)
		return (NULL);
	return (ft_strndup(subtoken, len));
}

char	*get_next_subtoken(char *token)
{
	static char	*remaining_token;
	char		*subtoken;

	if (token != NULL)
		remaining_token = token;
	if (!remaining_token || *remaining_token == '\0')
		return (NULL);
	subtoken = find_subtoken_start(remaining_token);
	remaining_token = find_str_subtoken_end(subtoken);
	if (subtoken == remaining_token)
		remaining_token = find_redir_subtoken_end(subtoken);
	return (duplicate_subtoken(subtoken, remaining_token));
}
