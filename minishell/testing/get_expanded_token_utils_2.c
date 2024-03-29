/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expanded_token_utils_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:18:41 by ychng             #+#    #+#             */
/*   Updated: 2024/03/24 04:26:43 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_backslash(char character)
{
	return (character == '\\');
}

bool	is_singlequoted(char character, bool is_double_quote)
{
	return (character == '\'' && !is_double_quote);
}

bool	is_double_quoted(char character, bool is_singlequote)
{
	return (character == '\"' && !is_singlequote);
}

bool	is_dollar_sign(char character, bool is_singlequote)
{
	return (character == '$' && !is_singlequote);
}
