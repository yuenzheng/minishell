/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:04:16 by ychng             #+#    #+#             */
/*   Updated: 2024/03/15 16:39:09 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	blt_pwd(void)
{
	char	*current_directory;

	current_directory = getcwd(NULL, 0);
	if (!current_directory)
		exit(1);
	printf("%s\n", current_directory);
	free(current_directory);
	exit(0);
}
