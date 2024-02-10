/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:26:05 by ychng             #+#    #+#             */
/*   Updated: 2024/02/10 22:02:10 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// int	count_num_of_non_empty_tokens(char **tokens)
// {
// 	int		i;
// 	int		j;
// 	int		token_count;
// 	bool	only_quotes;

// 	i = 0;
// 	token_count = 0;
// 	while (tokens[i])
// 	{
// 		j = 0;
// 		only_quotes = true;
// 		while (tokens[i][j])
// 		{
// 			if (tokens[i][j] != '\'' && tokens[i][j] != '\"')
// 			{
// 				only_quotes = false;
// 				break ;
// 			}
// 			j++;
// 		}
// 		if (!only_quotes)
// 			token_count++;
// 		i++;
// 	}
// 	return (token_count);
// }

bool	should_escape_in_double_quotes(char character)
{
	return (character == '\\' || character == '\"' || character == '$'
			|| character == '`');
}

void	expand_quotes(char *token)
{
	int		i;
	int		j;
	bool	escaped;
	bool	in_single_quote;
	bool	in_double_quote;

	i = 0;
	j = 0;
	escaped = false;
	in_single_quote = false;
	in_double_quote = false;
	while (token[i])
	{
		if (!escaped)
		{
			if (token[i] == '\\' && !in_single_quote)
				escaped = true;
			else if (token[i] == '\'' && !in_double_quote)
				in_single_quote = !in_single_quote;
			else if (token[i] == '\"' && !in_single_quote)
				in_double_quote = !in_double_quote;
			else
				token[j++] = token[i];
		}
		else
		{
			if (in_double_quote && should_escape_in_double_quotes(token[i]))
				token[j++] = token[i];
			else if (!in_single_quote || !in_double_quote)
				token[j++] = token[i];
			escaped = false;
		}
		i++;
	}
	token[j] = '\0';
}

// [hi, "  hi", "", 'hi  ']
char	**expand_tokens(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
		expand_quotes(tokens[i]);
}

int main(void)
{
	char	*user_input;
	char	**tokens;
	int		i;

	user_input = readline("> ");
	tokens = tokenize_user_input(user_input);
	expand_tokens(tokens);
	i = -1;
	while (tokens[++i])
		printf("%s\n", tokens[i]);
}
