/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:57:25 by ychng             #+#    #+#             */
/*   Updated: 2024/03/19 20:08:28 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	count_len_until_env(char *subtoken, char *env)
{
	int	len;

	len = 0;
	while (*subtoken && subtoken == ft_strstr(subtoken, env))
	{
		len++;
		subtoken++;
	}
	return (len);
}

char	*get_env_value(char *env, char **envp)
{
	char	*env_name;
	char	*env_value;
	int		env_name_len;

	env_name = env + 1;
	env_name_len = ft_strlen(env_name);
	while (*envp)
	{
		if (!ft_strncmp(env_name, *envp, env_name_len) \
			&& is_equal((*envp)[env_name_len]))
		{
			if (is_valid_syntax(*envp))
			{
				env_value = ft_strchr(*envp, '=') + 1;
				return (env_value);
			}
		}
		envp++;
	}
	return (NULL);
}

int	count_env_value_len(char *env, char **envp)
{
	char	*env_value;

	env_value = get_env_value(env, envp);
	return (ft_strlen(env_value));
}

int	skip_env(char *env)
{
	return (ft_strlen(env));
}

char	*append_env_value(char *result, char *env, char **envp)
{
	char	*env_value;

	env_value = get_env_value(env, envp);
	result = ft_strcat(result, env_value);
	result += ft_strlen(env_value);
	return (result);
}
