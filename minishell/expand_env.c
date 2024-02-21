/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 06:18:41 by ychng             #+#    #+#             */
/*   Updated: 2024/02/21 16:15:02 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// char	*expand_env(char *token)
// {
// 	char	*env;
// 	char	*result;

// 	env = get_next_env(token);
// 	result = malloc(sizeof(char) * (ft_strlen(token) + 1));
// 	if (!result)
// 	{
// 		printf("malloc failed for result\n");
// 		exit(-1);
// 	}
// 	while (env)
// 	{
// 		while (*token && token == ft_strstr(token, env))
// 			*result++ = *token++;
// 		token += ft_strlen(env);
// 		result = custom_strjoin(result, getenv(env + 1));
// 		free(env);
// 		env = get_next_env(NULL);
// 	}
// 	while (*token)
// 		*result++ = *token++;
// 	*result = '\0';
// }

int	count_len_until_env(char *token, char *env)
{
	int	len;

	len = 0;
	while (*token && token == ft_strstr(token, env))
	{
		len++;
		token++;
	}
	return (len);
}

int	count_env_value_len(char *env)
{
	char	*env_value;

	env = getenv(env + 1);
	return (ft_strlen(env));
}

int	skip_env(char *env)
{
	return (ft_strlen(env));
}

int	count_remaining_len(char *token)
{
	return (ft_strlen(token));
}

int	count_expanded_len(char *token)
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
	len += count_remaining_len(token);
	return (len);
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
	printf("%d\n", expanded_len);
	return (NULL);
}
