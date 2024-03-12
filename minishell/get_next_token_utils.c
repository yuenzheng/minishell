/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:58:20 by ychng             #+#    #+#             */
/*   Updated: 2024/03/12 19:35:02 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_control_operator(char *remaining_input)
{
	return (ft_strncmp(remaining_input, "|&", 2) == 0
		|| (ft_strncmp(remaining_input, "||", 2) == 0)
		|| (ft_strncmp(remaining_input, "&&", 2) == 0));
}
