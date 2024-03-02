/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:38:02 by ychng             #+#    #+#             */
/*   Updated: 2024/03/03 04:31:54 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*skip_n_options(char *subtoken)
{
	char	*n_option;
	char	*start;

	n_option = "-n";
	start = subtoken;
	if (ft_strncmp(start, n_option, 2) != 0)
		return (start);
	subtoken += ft_strlen(n_option);
	subtoken += ft_strspn(subtoken, "n");
	subtoken += ft_strspn(subtoken, " ");
	if (ft_strncmp(start, n_option, 2) == 0)
		return (start);
	return (skip_n_options(subtoken));
}

void	print_first_subtoken(t_subtoken_node *params)
{
	char	*first_subtoken;

	first_subtoken = skip_n_options(params->subtoken);
	if (*first_subtoken)
		printf("%s ", first_subtoken);
}

void	print_remaining_subtokens(t_subtoken_node *params)
{
	params = params->next;
	while (params)
	{
		printf("%s", params->subtoken);
		if (params->next != NULL)
			printf(" ");
		params = params->next;
	}
}
