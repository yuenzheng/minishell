/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:44:45 by ychng             #+#    #+#             */
/*   Updated: 2024/03/12 23:56:32 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_control_operator(char *str)
{
	return (ft_strncmp(str, "|&", 2) == 0
		|| (ft_strncmp(str, "||", 2) == 0)
		|| (ft_strncmp(str, "&&", 2) == 0));
}

bool	is_redirection(char *str)
{
	return (ft_strncmp(str, "<<<", 3) == 0
		|| (ft_strncmp(str, "<<", 2) == 0)
		|| (ft_strncmp(str, ">>", 2) == 0)
		|| (ft_strncmp(str, "<", 1) == 0)
		|| (ft_strncmp(str, ">", 1) == 0)
		|| (ft_strncmp(str, "|", 1) == 0));
}

bool	is_heredoc(char *str)
{
	return (ft_strcmp(str, "<<") == 0);
}
