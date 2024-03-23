/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:47:46 by ychng             #+#    #+#             */
/*   Updated: 2024/03/24 04:29:46 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	toggle_inquote(char c, bool *inquote, char *quote_type)
{
	if (*inquote == false)
	{
		*inquote = true;
		*quote_type = c;
	}
	else if (c == *quote_type)
	{
		*inquote = false;
		*quote_type = '\0';
	}
}
