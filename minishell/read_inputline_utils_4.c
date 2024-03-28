/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline_utils_4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 00:00:47 by ychng             #+#    #+#             */
/*   Updated: 2024/03/29 00:01:29 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	validlen(char *token, int *openbrackets)
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
			break ;
		token++;
	}
	return (token - start);
}

int	validlenredir(char *token)
{
	char		*start;
	char		*lastredir;
	int			openredirs;

	openredirs = 0;
	start = token;
	while (*token)
	{
		if (is_redirection_n(token) && (openredirs == 0))
		{
			lastredir = token;
			openredirs++;
			token += redirlen(token);
			continue ;
		}
		else if (!is_space(*token) && is_notvalidname(token) && openredirs > 0)
			return (lastredir - start);
		else if (!is_space(*token) && openredirs > 0)
			openredirs--;
		token++;
	}
	if (openredirs > 0)
		return (lastredir - start);
	return (token - start);
}

char	*extract_heredoc(char *input, int joinedlen)
{
	char	*joinedtokens;
	char	*subtoken;
	char	*result;

	joinedtokens = ft_strndup(input, joinedlen);
	if (!joinedtokens)
	{
		printf("ft_strndup failed for joinedtokens\n");
		free(input);
		exit(-1);
	}
	// subtoken = get_next_subtoken(joinedtokens);
	// while (subtoken)
	// {
	// 	if (is_heredoc(subtoken))
	// 	{
	// 		result = custom_strjoin(result, subtoken);
	// 		// i was planning to just joined each heredoc with their name
	// 		// problem im facing
	// 		// what if no name exist or name is an error
	// 		// <<, << ||, << (.
	// 	}
	// 	subtoken = get_next_subtoken(NULL);
	// }
	return (ft_strndup(input, joinedlen));
}
