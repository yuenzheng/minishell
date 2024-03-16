/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_double_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:04:33 by ychng             #+#    #+#             */
/*   Updated: 2024/03/16 20:15:20 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	count_num_of_items(char **double_array)
{
	int	count;

	count = 0;
	while (double_array[count])
		count++;
	return (count);
}

char	**clone_double_array(char **double_array)
{
	int		total_size;
	char	**result;
	int		i;

	total_size = count_num_of_items(double_array) + 1;
	result = malloc(sizeof(char *) * total_size);
	if (result == NULL)
	{
		printf("malloc failed for result\n");
		exit(-1);
	}
	i = -1;
	while (double_array[++i])
	{
		result[i] = ft_strdup(double_array[i]);
		if (result[i] == NULL)
		{
			printf("ft_strdup failed for result[%d]\n", i);
			exit(-1);
		}
	}
	result[i] == NULL;
	return (result);
}
