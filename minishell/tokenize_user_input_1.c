/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_user_input_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 04:45:59 by ychng             #+#    #+#             */
/*   Updated: 2024/02/03 18:03:00 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	count_num_of_tokens(char *user_input)
{
	int		i;
	int		token_count;
	int		nesting_lvl;
	char	open_char;

	i = 0;
	token_count = 0;
	nesting_lvl = 0;
	open_char = '\0';
	while (user_input[i])
	{
		while (is_whitespace_char(user_input[i]))
			i++;
		if (user_input[i] && !open_char)
			token_count++;
		while (user_input[i] && !is_whitespace_char(user_input[i]))
			process_char_in_token(user_input[i], &open_char, &nesting_lvl, &i);
	}
	return (token_count);
}

static int	count_token_len(char *user_input)
{
	int		i;
	int		nesting_lvl;
	char	open_char;

	i = 0;
	nesting_lvl = 0;
	open_char = '\0';
	while (user_input[i] && (!is_whitespace_char(user_input[i]) || open_char))
		process_char_in_token(user_input[i], &open_char, &nesting_lvl, &i);
	return (i);
}

static char	*get_single_token(char *user_input)
{
	int		token_len;
	char	*token;
	int		i;

	token_len = count_token_len(user_input);
	token = malloc(sizeof(char) * (token_len + 1));
	if (!token)
	{
		printf("malloc failed for token\n");
		exit(-1);
	}
	i = -1;
	while (++i < token_len)
		token[i] = user_input[i];
	token[i] = '\0';
	return (token);
}

static void	add_tokens(char **tokens, char *user_input)
{
	int		i;
	int		j;
	int		nesting_lvl;
	char	open_char;

	i = 0;
	j = 0;
	nesting_lvl = 0;
	open_char = '\0';
	while (user_input[i])
	{
		while (is_whitespace_char(user_input[i]))
			i++;
		if (user_input[i] && !open_char)
			tokens[j++] = get_single_token(user_input + i);
		while (user_input[i] && !is_whitespace_char(user_input[i]))
			process_char_in_token(user_input[i], &open_char, &nesting_lvl, &i);
	}
	tokens[j] = NULL;
}

char	**tokenize_user_input(char *user_input)
{
	int		num_of_tokens;
	char	**tokens;

	num_of_tokens = count_num_of_tokens(user_input);
	tokens = malloc(sizeof(char *) * (num_of_tokens + 1));
	if (!tokens)
	{
		printf("malloc failed for tokens\n");
		exit(-1);
	}
	add_tokens(tokens, user_input);
	return (tokens);
}

// int	main(void)
// {
// 	char	*user_input;
// 	char	**tokens;
// 	int		i;

// 	user_input = readline("> ");
// 	tokens = tokenize_user_input(user_input);
// 	i = -1;
// 	while (tokens[++i])
// 		printf("%s\n", tokens[i]);
// }