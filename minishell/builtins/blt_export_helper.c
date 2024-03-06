/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:41:33 by ychng             #+#    #+#             */
/*   Updated: 2024/03/07 00:58:20 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pad_export_envp(char **export_envp)
{
	int	max_len;

	max_len = get_max_name_len(export_envp);
	while (*export_envp)
	{
		*export_envp = pad_name(*export_envp, max_len);
		export_envp++;
	}
}

static void	count_sort(char **export_envp, int export_envp_size, int pos)
{
	int		i;
	int		count[256];
	char	**output;

	ft_bzero(count, sizeof(int) * 256);
	i = 0;
	while (i < export_envp_size)
		count[export_envp[i++][pos]]++;
	i = 1;
	while (i < 256)
	{
		count[i] += count[i - 1];
		i++;
	}
	output = create_output(export_envp_size);
	i = export_envp_size;
	while (i--)
		output[--count[export_envp[i][pos]]] = export_envp[i];
	ft_memcpy(export_envp, output, sizeof(char *) * export_envp_size);
	free(output);
}

void	radix_sort(char **export_envp)
{
	int	pos;

	pos = get_max_name_len(export_envp);
	while (pos--)
		count_sort(export_envp, count_envp_size(export_envp), pos);
}

void	print_export_envp(char **export_envp)
{
	char	*entry_copy;
	char	*name;
	char	*value;

	while (*export_envp)
	{
		if (is_underscore(**export_envp) && *(*export_envp + 1) == ' ')
		{
			export_envp++;
			continue ;
		}
		entry_copy = ft_strdup(*export_envp);
		name = ft_strtrim(ft_strtok(entry_copy, "="), " ");
		value = ft_strchr(*export_envp, '=');
		if (value)
		{
			value++;
			printf("declare -x %s=\"%s\"\n", name, value);
		}
		else
			printf("declare -x %s\n", name);
		free(entry_copy);
		free(name);
		export_envp++;
	}
}

void	free_export_envp(char **export_envp)
{
	int	i;

	i = -1;
	while (export_envp[++i])
		free(export_envp[i]);
	free(export_envp);
}
