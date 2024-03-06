/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 03:40:06 by ychng             #+#    #+#             */
/*   Updated: 2024/03/07 02:48:18 by ychng            ###   ########.fr       */
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
