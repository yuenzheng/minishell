/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:41:33 by ychng             #+#    #+#             */
/*   Updated: 2024/03/06 23:10:13 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**create_output(int export_envp_size)
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
