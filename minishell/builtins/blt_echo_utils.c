/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:38:02 by ychng             #+#    #+#             */
/*   Updated: 2024/03/03 02:27:19 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*skip_n_options(char *subtoken)
{
	char	*flag;
	char	*start;

	flag = "-n";
	start = subtoken;
	while (ft_strncmp(subtoken, flag, 2) == 0)
	{
		subtoken += ft_strlen(flag);
		subtoken += ft_strspn(subtoken, "n");
		if (is_space(*subtoken) || (*subtoken == '\0'))
		{
			subtoken += ft_strspn(subtoken, " ");
			start = subtoken;
		}
	}
	return (start);
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
