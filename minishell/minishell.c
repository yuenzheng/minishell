/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:56:25 by ychng             #+#    #+#             */
/*   Updated: 2024/02/21 21:10:10 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	char	*input;
	char	*token;

	while (1)
	{
		input = get_input_line();
		token = custom_strtok(input, " ");
		while (token)
		{
			expand_env(token);
			expand_tilde(token);
			token = custom_strtok(NULL, " ");
		}
		free(input);
	}
}
