/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:26:19 by ychng             #+#    #+#             */
/*   Updated: 2024/03/07 19:38:44 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// I got an if condition to check if its an empty str
// because of my own blt_unset, which will replace the string
// with an empty string instead, so if it's empty stirng
// I don't print anything
int	blt_env(char **envp)
{
	while (*envp)
	{
		if (**envp != '\0')
			printf("%s\n", *envp);
		envp++;
	}
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	envp[0] = "";
// 	blt_env(envp);
// }