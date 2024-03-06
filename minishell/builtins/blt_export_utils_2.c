/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 03:53:03 by ychng             #+#    #+#             */
/*   Updated: 2024/03/07 00:58:05 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	validate_entry_name(char *subtoken)
{
	if (is_special_env_name(*subtoken))
		return (false);
	while (*subtoken && is_valid_env_name(*subtoken))
		subtoken++;
	return (is_equal(*subtoken) || *subtoken == '\0');
}

int	get_max_name_len(char **export_envp)
{
	int	max_len;
	int	len;

	max_len = 0;
	while (*export_envp)
	{
		len = ft_strcspn(*export_envp, "=");
		if (max_len < len)
			max_len = len;
		export_envp++;
	}
	return (max_len);
}

char	*pad_name(char *entry, int max_name_len)
{
	int		name_len;
	char	*padded_name;
	char	*remaining_entry;
	char	*new_entry;

	name_len = ft_strcspn(entry, "=");
	if (name_len < max_name_len)
	{
		padded_name = ft_strndup(entry, name_len);
		padded_name = ft_realloc(padded_name, name_len + 1, max_name_len + 1);
		if (!padded_name)
		{
			printf("malloc failed for padded_name\n");
			exit(-1);
		}
		ft_memset(padded_name + name_len, ' ', max_name_len - name_len);
		padded_name[max_name_len] = '\0';
		remaining_entry = ft_strchr(entry, '=');
		new_entry = custom_strjoin(padded_name, remaining_entry);
		free(entry);
		return (new_entry);
	}
	return (entry);
}

char	**create_output(int export_envp_size)
{
	char	**output;

	output = malloc(sizeof(char *) * export_envp_size);
	if (!output)
	{
		printf("malloc failed for output\n");
		exit(-1);
	}
	return (output);
}
