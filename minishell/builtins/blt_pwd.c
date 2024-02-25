/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:04:16 by ychng             #+#    #+#             */
/*   Updated: 2024/02/25 18:32:56 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	blt_pwd(void)
{
	char	*current_directory;

	current_directory = getcwd(NULL, 0);
	if (!current_directory)
		return (1);
	printf("%s\n", current_directory);
	free(current_directory);
	return (0);
}
