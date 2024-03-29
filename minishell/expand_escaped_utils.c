/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_escaped_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:29:04 by ychng             #+#    #+#             */
/*   Updated: 2024/03/24 04:26:43 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	should_escape(char quote_type, char *subtoken)
{
	if (is_singlequote(quote_type) || !is_backslash(*subtoken))
		return (false);
	if (is_double_quote(quote_type) && is_escapable(*(subtoken + 1)))
		return (true);
	if (!is_double_quote(quote_type))
		return (true);
	return (false);
}
