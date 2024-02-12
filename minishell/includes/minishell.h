/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:07:02 by ychng             #+#    #+#             */
/*   Updated: 2024/02/12 19:21:21 by ychng            ###   ########.fr       */
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

#endif
