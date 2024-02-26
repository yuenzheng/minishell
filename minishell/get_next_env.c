/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:04:02 by ychng             #+#    #+#             */
/*   Updated: 2024/02/26 17:49:00 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*find_env_start(char *remaining_token)
{
	bool	escaped;
	bool	in_quote;
	char	quote_type;

	escaped = false;
	in_quote = false;
	quote_type = '\0';
	while (*remaining_token)
	{
		if (!escaped && !is_single_quote(quote_type)
			&& is_backslash(*remaining_token))
			escaped = true;
		else if (!escaped && is_quote(*remaining_token))
			toggle_in_quote(*remaining_token, &in_quote, &quote_type);
		else if (!escaped && !is_single_quote(quote_type)
			&& is_env_var(remaining_token))
			break ;
		else
			escaped = false;
		remaining_token++;
	}
	return (remaining_token);
}

static char	*skip_env_name(char *remaining_token)
{
	if (is_dollar_sign(*remaining_token))
	{
		remaining_token++;
		if (is_special_env_name(*remaining_token))
		{
			remaining_token++;
			return (remaining_token);
		}
		while (*remaining_token && is_valid_env_name(*remaining_token))
			remaining_token++;
	}
	return (remaining_token);
}

static char	*duplicate_env_var(char *env, char *remaining_token)
{
	int	len;

	len = remaining_token - env;
	if (len == 0)
		return (NULL);
	return (ft_strndup(env, len));
}

char	*get_next_env(char *token)
{
	static char	*remaining_token;
	char		*env;

	if (token != NULL)
		remaining_token = token;
	if (!remaining_token || *remaining_token == '\0')
		return (NULL);
	remaining_token = find_env_start(remaining_token);
	env = remaining_token;
	remaining_token = skip_env_name(remaining_token);
	return (duplicate_env_var(env, remaining_token));
}

// int	main(void)
// {
// 	char	*token;
// 	char	*env;

// 	token = readline("> ");
// 	env = get_next_env(token);
// 	while (env)
// 	{
// 		printf("%s\n", env);
// 		env = get_next_env(NULL);
// 	}
// }