/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:07:02 by ychng             #+#    #+#             */
/*   Updated: 2024/02/01 16:30:42 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "sys_headers.h"
# include "libft.h"

// tokenize_user_input_2.c
void	process_non_whitespace_char(
			char *user_input, char *open_char, int *nesting_level, int *i);
// tokenize_user_input_1.c
char	**tokenize_user_input(char *user_input);

// tokenize_user_input_utils_2.c
bool	is_whitespace_char(char current_char);
// tokenize_user_input_utils_1.c
bool	can_be_nested_char(char current_char, char next_char);
bool	is_quote_char(char current_char);
bool	is_open_char(char current_char, char next_char);
bool	is_matching_close_char(char current_char, char open_char);
bool	is_escape_char(char current_char, char next_char);

#endif
