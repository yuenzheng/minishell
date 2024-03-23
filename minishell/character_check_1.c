/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_check_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:41:55 by ychng             #+#    #+#             */
/*   Updated: 2024/03/24 04:26:43 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_backslash(char c)
{
	return (c == '\\');
}

bool	is_singlequote(char c)
{
	return (c == '\'');
}

bool	is_double_quote(char c)
{
	return (c == '\"');
}

bool	is_quote(char c)
{
	return (is_singlequote(c) || is_double_quote(c));
}

bool	is_delim(char c, char *delim)
{
	return (ft_strchr(delim, c));
}
