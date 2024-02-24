/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:38:02 by ychng             #+#    #+#             */
/*   Updated: 2024/02/24 15:08:02 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*skip_n_options(char *token)
{
	char	*flag;
	char	*start;

	flag = "-n";
	start = token;
	while (ft_strncmp(token, flag, 2) == 0)
	{
		token += ft_strlen(flag);
		token += ft_strspn(token, "n");
		if (is_space(*token) || (*token == '\0'))
		{
			token += ft_strspn(token, " ");
			start = token;
		}
	}
	return (start);
}

void	print_first_token(t_token_node *params)
{
	char	*first_token;

	first_token = skip_n_options(params->token);
	if (*first_token)
		printf("%s ", first_token);
}

void	print_rest_of_tokens(t_token_node *params)
{
	params = params->next;
	while (params)
	{
		printf("%s", params->token);
		if (params->next != NULL)
			printf(" ");
		params = params->next;
	}
}
