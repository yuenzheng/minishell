/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:47:46 by ychng             #+#    #+#             */
/*   Updated: 2024/02/18 18:49:47 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	toggle_in_quote(char c, bool *in_quote, char *quote_type)
{
	if (*in_quote == false)
	{
		*in_quote = true;
		*quote_type = c;
	}
	else if (c == *quote_type)
	{
		*in_quote = false;
		*quote_type = '\0';
	}
}
