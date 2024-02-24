/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_escaped_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:29:04 by ychng             #+#    #+#             */
/*   Updated: 2024/02/24 18:58:23 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	should_escape(char quote_type, char *token)
{
	if (is_single_quote(quote_type) || !is_backslash(*token))
		return (false);
	if (is_double_quote(quote_type) && is_escapable(*(token + 1)))
		return (true);
	if (!is_double_quote(quote_type))
		return (true);
	return (false);
}
