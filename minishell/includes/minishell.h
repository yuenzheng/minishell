/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:07:02 by ychng             #+#    #+#             */
/*   Updated: 2024/02/16 20:49:26 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "sys_headers.h"
# include "libft.h"

typedef struct s_node
{
	char			*token;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_stack
{
	t_node	*head;
	t_node	*tail;
}	t_stack;

typedef struct s_token_state
{
	bool	escaped;
	bool	in_single_quote;
	bool	in_double_quote;
	int		token_len;
}	t_token_state;

// tokenize_user_input_2.c
void	process_char_in_token(
			char *user_input,
			char *open_delim,
			int *nesting_lvl,
			int *i
			);
// tokenize_user_input_1.c
char	**tokenize_user_input(char *user_input);

// tokenize_user_input_utils_2.c
bool	is_whitespace_char(char character);
bool	is_quote_char(char character);
bool	is_left_bracket_char(char character);
// tokenize_user_input_utils_1.c
bool	is_open_delim(char current_char);
bool	is_nested_delim(char current_char);
bool	is_close_delim(char current_char, char open_delim);
bool	is_escaped_char(char current_char, char next_char, char open_delim);

// get_expanded_token_utils_2.c
bool	is_backslash(char character);
bool	is_single_quoted(char character, bool is_double_quote);
bool	is_double_quoted(char character, bool is_single_quote);
bool	is_dollar_sign(char character, bool is_single_quote);
// get_expanded_token_utils_1.c
int		get_expanded_token_len(char *token);

#endif
