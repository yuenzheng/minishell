/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:07:02 by ychng             #+#    #+#             */
/*   Updated: 2024/02/21 06:22:52 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "sys_headers.h"
# include "libft.h"

// character_check_1.c
bool	is_backslash(char c);
bool	is_single_quote(char c);
bool	is_double_quote(char c);
bool	is_quote(char c);
bool	is_delim(char c, char *delim);

// character_check_2.c
bool	is_underscore(char c);
bool	is_hash(char c);
bool	is_dollar_sign(char c);
bool	is_asterisk(char c);
bool	is_ampersand(char c);

// character_check_3.c
bool	is_question_mark(char c);
bool	is_exclamation(char c);
bool	is_number(char c);
bool	is_uppercase(char c);
bool	is_lowercase(char c);

// quote_handling.c
void	toggle_in_quote(char c, bool *in_quote, char *quote_type);

// custom_strtok.c
char	*custom_strtok(char *input, char *delim);

// env_check.c
bool	is_special_env_name(char c);
bool	is_valid_env_name(char c);
bool	is_env_var(char *remaining_input);

// get_next_env.c
char	*get_next_env(char *token);

// get_input_line.c
char	*get_input_line(void);

// expand_env.c
char	*expand_env(char *token);

#endif
