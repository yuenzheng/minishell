/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:41:55 by ychng             #+#    #+#             */
/*   Updated: 2024/02/18 18:46:05 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_backslash(char c)
{
	return (c == '\\');
}

bool	is_single_quote(char c)
{
	return (c == '\'');
}

bool	is_double_quote(char c)
{
	return (c == '\"');
}

bool	is_quote(char c)
{
	return (is_single_quote(c) || is_double_quote(c));
}

bool	is_delim(char c, char *delim)
{
	return (ft_strchr(delim, c));
}
