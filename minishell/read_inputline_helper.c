/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:20:21 by ychng             #+#    #+#             */
/*   Updated: 2024/03/27 01:20:02 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	update_history(char *input)
{
	static char	*previnput;

	if (previnput && !ft_strcmp(previnput, input) && !contains_newline(input))
		return ;
	if (previnput != NULL)
		free(previnput);
	previnput = ft_strdup(input);
	if (!previnput)
	{
		printf("ft_strdup failed for previnput\n");
		exit(-1);
	}
	add_history(previnput);
}
