/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 04:46:21 by ychng             #+#    #+#             */
/*   Updated: 2024/02/25 05:18:02 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	contain_only_numbers(char *first_arg)
{
	first_arg += ft_strspn(first_arg, " ");
	if (*first_arg == '+' || *first_arg == '-')
		first_arg++;
	if (!is_number(*first_arg))
		return (false);
	return (ft_strspn(first_arg, "0123456789 ") == ft_strlen(first_arg));
}

int	normalize_exit_code(char *first_arg)
{
	int	value;

	value = ft_atoi(first_arg);
	if (value > 0)
		return (value % 256);
	return ((value + 256) % 256);
}

void	handle_numeric_exit(char *first_arg, char *dup_token)
{
	int	exit_code;

	exit_code = normalize_exit_code(first_arg);
	free(dup_token);
	exit(exit_code);
}

void	handle_non_numeric_exit(char *dup_token)
{
	printf("numeric argument required\n");
	free(dup_token);
	exit(255);
}
