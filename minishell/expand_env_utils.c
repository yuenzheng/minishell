/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:57:25 by ychng             #+#    #+#             */
/*   Updated: 2024/02/21 20:20:28 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

char	*get_env_value(char *env)
{
	return (getenv(env + 1));
}

int	count_env_value_len(char *env)
{
	char	*env_value;

	env_value = get_env_value(env);
	return (ft_strlen(env_value));
}

int	skip_env(char *env)
{
	return (ft_strlen(env));
}

char	*append_env_value(char *result, char *env)
{
	char	*env_value;

	env_value = get_env_value(env);
	result = ft_strcat(result, env_value);
	result += ft_strlen(env_value);
	return (result);
}
