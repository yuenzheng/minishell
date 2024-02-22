/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 06:18:41 by ychng             #+#    #+#             */
/*   Updated: 2024/02/22 19:17:39 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	count_expanded_len(char *token)
{
	int		len;
	char	*env;

	len = 0;
	env = get_next_env(token);
	while (env)
	{
		len += count_len_until_env(token, env);
		len += count_env_value_len(env);
		token += skip_env(env);
		free(env);
		env = get_next_env(NULL);
	}
	len += ft_strlen(token);
	return (len);
}

static void	fill_result(char *result, char *token)
{
	char	*env;

	env = get_next_env(token);
	while (env)
	{
		while (*token && token != ft_strstr(token, env))
			*result++ = *token++;
		*result = '\0';
		result = append_env_value(result, env);
		token += skip_env(env);
		free(env);
		env = get_next_env(NULL);
	}
	*result = '\0';
	ft_strcat(result, token);
}

char	*expand_env(char *token)
{
	char	*result;
	int		expanded_len;

	expanded_len = count_expanded_len(token);
	result = malloc(sizeof(char) * (expanded_len + 1));
	if (!result)
	{
		printf("malloc failed for result\n");
		exit(-1);
	}
	fill_result(result, token);
	return (result);
}
