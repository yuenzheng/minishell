/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:44:45 by ychng             #+#    #+#             */
/*   Updated: 2024/03/28 02:21:03 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_logicalop(char *str)
{
	return (ft_strcmp(str, "||") == 0
		|| (ft_strcmp(str, "&&") == 0));
}

bool	is_logicalop_n(char *str)
{
	return (ft_strncmp(str, "||", 2) == 0
		|| (ft_strncmp(str, "&&", 2) == 0));
}

bool	is_redirection(char *str)
{
	return (ft_strcmp(str, "<<<") == 0
		|| (ft_strcmp(str, "<<") == 0)
		|| (ft_strcmp(str, ">>") == 0)
		|| (ft_strcmp(str, "<") == 0)
		|| (ft_strcmp(str, ">") == 0)
		|| (ft_strcmp(str, "|") == 0));
}

bool	is_redirection_n(char *str)
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
