/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:44:37 by ychng             #+#    #+#             */
/*   Updated: 2024/03/11 13:17:07 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	count_sort(char **export_envp, int export_envp_size, int pos)
{
	int		i;
	int		count[256];
	char	**output;

	ft_bzero(count, sizeof(int) * 256);
	i = 0;
	while (i < export_envp_size)
	{
		count[(unsigned char)export_envp[i][pos]]++;
		i++;
	}
	i = 1;
	while (i < 256)
	{
		count[i] += count[i - 1];
		i++;
	}
	output = create_output(export_envp_size);
	i = export_envp_size;
	while (i--)
		output[--count[(unsigned char)export_envp[i][pos]]] = export_envp[i];
	ft_memcpy(export_envp, output, sizeof(char *) * export_envp_size);
	free(output);
}
