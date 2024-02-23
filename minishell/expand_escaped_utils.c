/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_escaped_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:29:04 by ychng             #+#    #+#             */
/*   Updated: 2024/02/23 20:53:15 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	should_escape(char quote_type, char *token)
{
	return (!is_single_quote(quote_type) && is_backslash(*token)
		&& needs_escaping(quote_type, *(token + 1)));
}

bool	needs_escaping(char quote_type, char next_c)
{
	return ((is_double_quote(quote_type) && is_escapable(next_c))
		|| (!is_double_quote(quote_type)));
}
