/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_list_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:27:06 by ychng             #+#    #+#             */
/*   Updated: 2024/03/13 19:55:18 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*expand_subtoken(char *subtoken, bool expand_heredoc)
{
	if (expand_heredoc)
	{
		subtoken = expand_escaped(subtoken);
	}
	else
	{
		subtoken = expand_tilde(subtoken);
		subtoken = expand_env(subtoken);
		subtoken = expand_escaped(subtoken);
	}
	return (subtoken);
}
