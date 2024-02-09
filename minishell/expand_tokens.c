/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:26:05 by ychng             #+#    #+#             */
/*   Updated: 2024/02/09 18:18:26 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	count_num_of_non_empty_tokens(char **tokens)
{
	int		i;
	int		j;
	int		token_count;
	bool	only_quotes;

	i = 0;
	token_count = 0;
	while (tokens[i])
	{
		j = 0;
		only_quotes = true;
		while (tokens[i][j])
		{
			if (tokens[i][j] != '\'' && tokens[i][j] != '\"')
			{
				only_quotes = false;
				break ;
			}
			j++;
		}
		if (!only_quotes)
			token_count++;
		i++;
	}
	return (token_count);
}

char	**expand_tokens(char **tokens)
{
	int		token_count;
	char	**expanded_tokens;

	token_count = count_num_of_non_empty_tokens(tokens);
	expanded_tokens = malloc(sizeof(char *) * token_count);
	if (!expanded_tokens)
	{
		// FREE tokens
		printf("malloc failed for expanded_tokens\n");
		exit(-1);
	}
	fill_expanded_tokens();
}

int main(void)
{
	char	*user_input;
	char	**tokens;
	int		i;

	user_input = readline("> ");
	tokens = tokenize_user_input(user_input);
	i = -1;
	while (tokens[++i])
		printf("%s %d\n", tokens[i], count_num_of_non_empty_tokens(tokens));
}
