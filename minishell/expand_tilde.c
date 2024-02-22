/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:28:13 by ychng             #+#    #+#             */
/*   Updated: 2024/02/22 19:18:01 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// char	*expand_tilde_in_token(char *token, char *env_value)
// {
// 	char	*result;
// 	int		tilde_len;
// 	int		joined_len;

// 	tilde_len = 1;
// 	joined_len = ft_strlen(token) + ft_strlen(env_value) - tilde_len;
// 	result = malloc(sizeof(char) * (joined_len + 1));
// 	if (!result)
// 	{
// 		printf("malloc failed for result\n");
// 		exit(-1);
// 	}
// 	*result = '\0';
// 	ft_strcpy(result, env_value);
// 	ft_strcat(result, token + 1);
// 	return (result);
// }

char	*expand_tilde(char *token)
{
	(void)token;
	return (NULL);
}
