/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline_utils_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 01:39:11 by ychng             #+#    #+#             */
/*   Updated: 2024/03/27 01:42:35 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


bool	has_logicaloperr(char *token, int *openlogicalops)
{
	if (is_logicalop(token) == true)
	{
		(*openlogicalops)++;
		if (*openlogicalops > 0)
		{
			printf(
				"syntax error near unexpected token `%c%c'\n", \
				token[0], token[1]);
			return (true);
		}
	}
	else if (ft_strspn(token, " ") != ft_strlen(token))
		(*openlogicalops)--;
	return (false);
}

// bool	is_empty(char *start, char *token)
// {
// 	while (token >= start)
// 	{
// 		if (is_leftbracket(*token))
// 			return (true);
// 		if (!is_space(*token) && !is_rightbracket(*token))
// 			return (false);
// 		token--;
// 	}
// 	return (true);
// }

bool	has_bracketerr(char *token, int *openbrackets)
{
	char	*start;

	token += ft_strspn(token, " ");
	start = token;
	while (*token)
	{
		if (((start == token) || *openbrackets > 0) && is_leftbracket(*token))
			(*openbrackets)++;
		else if (((start != token) && *openbrackets > 0) && is_rightbracket(*token))
			(*openbrackets)--;
		else if (((start == token) && is_rightbracket(*token)) \
			|| ((start != token) && is_bracket(*token)))
		{
			printf("syntax error near unexpected token `%c'\n", *token);
			return (true);
		}
		token++;
	}
	return (false);
}
