/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:26:05 by ychng             #+#    #+#             */
/*   Updated: 2024/02/16 20:22:16 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
