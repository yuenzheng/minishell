/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 03:53:03 by ychng             #+#    #+#             */
/*   Updated: 2024/03/06 03:54:00 by ychng            ###   ########.fr       */
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
