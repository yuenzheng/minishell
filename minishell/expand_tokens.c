/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:26:05 by ychng             #+#    #+#             */
/*   Updated: 2024/02/15 19:08:41 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_alphabet(char character)
{
	return (character >= 'A' && character <= 'Z'
		|| (character >= 'a' && character <= 'z'));
}

int	get_env_value_len(char *token, int *i)
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

void	handle_quotes(
	char character, bool *in_single_quote, bool *in_double_quote)
{
	if (character == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	else if (character == '\"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
}

int	get_expanded_token_len(char *token)
{
	int		i;
	bool	in_double_quote;
	bool	in_single_quote;
	int		new_token_len;

	i = 0;
	in_single_quote = false;
	in_double_quote = false;
	new_token_len = 0;
	while (token[i])
	{
		handle_quotes(token[i], &in_single_quote, &in_double_quote);
		if (token[i] == '$' && !in_single_quote)
		{
			new_token_len += get_env_value_len(token, &i);
			continue ;
		}
		else if (token[i] == '\\' && token[i + 1] != '\0')
		{
			new_token_len++;
			i++;
		}
		new_token_len++;
		i++;
	}
	return (new_token_len);
}

char	**expand_tokens(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
		printf("%d\n", get_expanded_token_len(tokens[i]));
	return (NULL);
}

int main(void)
{
	char	*user_input;
	char	**tokens;
	int		i;

	user_input = readline("> ");
	tokens = tokenize_user_input(user_input);
	expand_tokens(tokens);
	// i = -1;
	// while (tokens[++i])
	// 	printf("%s\n", tokens[i]);
}
