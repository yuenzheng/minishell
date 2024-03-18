/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:44:22 by ychng             #+#    #+#             */
/*   Updated: 2024/03/19 02:26:01 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_max_env_name_len(char **envp)
{
	int	max_len;
	int	len;

	max_len = 0;
	while (*envp)
	{
		len = ft_strcspn(*envp, "=");
		if (max_len < len)
			max_len = len;
		envp++;
	}
	return (max_len);
}

char	*pad_env_name(char *entry, int max_len)
{
	int		env_name_len;
	char	*result;

	env_name_len = ft_strcspn(entry, "=");
	if (env_name_len < max_len)
	{
		result = ft_strndup(entry, env_name_len);
		result = ft_realloc(result, env_name_len + 1, max_len + 1);
		if (!result)
		{
			printf("ft_realloc failed for result\n");
			exit(-1);
		}
		ft_memset(&result[env_name_len], ' ', max_len - env_name_len);
		result[max_len] = '\0';
		result = custom_strjoin(result, ft_strchr(entry, '='));
		free(entry);
		return (result);
	}
	return (entry);
}

char	*trim_env_name_pad(char *entry)
{
	int		old_size;
	int		new_size;
	char	*result;

	old_size = ft_strcspn(entry, "=");
	new_size = ft_strcspn(entry, " ");
	result = ft_realloc(ft_strndup(entry, old_size), old_size + 1, new_size + 1);
	if (!result)
	{
		printf("ft_realloc failed for result\n");
		exit(-1);
	}
	result[new_size] = '\0';
	result = custom_strjoin(result, ft_strchr(entry, '='));
	free(entry);
	return (result);
}
