/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:07:02 by ychng             #+#    #+#             */
/*   Updated: 2024/02/18 18:59:00 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "sys_headers.h"
# include "libft.h"

// character_check.c
bool	is_backslash(char c);
bool	is_single_quote(char c);
bool	is_double_quote(char c);
bool	is_quote(char c);
bool	is_delim(char c, char *delim);

// quote_handling.c
void	toggle_in_quote(char c, bool *in_quote, char *quote_type);

// get_next_token.c
char	*get_next_token(char *input, char *delim);

#endif
