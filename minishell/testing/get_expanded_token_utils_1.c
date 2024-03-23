/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expanded_token_utils_1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:54:13 by ychng             #+#    #+#             */
/*   Updated: 2024/03/24 04:26:43 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static bool	is_alphabet(char character)
{
	return (character >= 'A' && character <= 'Z'
		|| (character >= 'a' && character <= 'z'));
}

static int	get_expanded_env_len(char *token, int *i)
{
	int		j;
	char	*env;
	char	*env_value;

	j = *i + 1;
	while (token[j] && is_alphabet(token[j]))
		j++;
	env = ft_substr(token, *i + 1, j - *i - 1);
	env_value = getenv(env);
	free(env);
	*i = j;
	return (ft_strlen(env_value));
}

int	process_token_character(char *token, int *i, t_token_state *state)
{
	bool	escaped;
	bool	in_double_quote;
	bool	in_single_quote;

	escaped = state->escaped;
	in_single_quote = state->in_single_quote;
	in_double_quote = state->in_double_quote;
	if (!escaped && is_backslash(token[*i]))
		state->escaped = true;
	else if (!escaped && is_singlequoted(token[*i], in_double_quote))
		state->in_single_quote = !state->in_single_quote;
	else if (!escaped && is_double_quoted(token[*i], in_single_quote))
		state->in_double_quote = !state->in_double_quote;
	else if (!escaped && is_dollar_sign(token[*i], in_single_quote))
	{
		state->token_len += get_expanded_env_len(token, i);
		return (1);
	}
	else
		state->escaped = false;
	state->token_len++;
	return (0);
}

int	get_expanded_token_len(char *token)
{
	int				i;
	t_token_state	state;

	i = 0;
	state = (t_token_state){0};
	while (token[i])
	{
		if (process_token_character(token, &i, &state) == 0)
			i++;
	}
	return (state.token_len);
}
