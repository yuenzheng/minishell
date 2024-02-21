/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 06:18:41 by ychng             #+#    #+#             */
/*   Updated: 2024/02/21 13:08:18 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*custom_strjoin()
{
}

// hi$HOME,$USER
char	*expand_env(char *token)
{
	char	*env;

	env = get_next_env(token);
	while (env)
	{
		
		free(env);
		env = get_next_env(NULL);
	}
}
