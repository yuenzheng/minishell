/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:44:19 by ychng             #+#    #+#             */
/*   Updated: 2024/02/29 17:03:22 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Don't need to free subtoken in here,
// Becase i'm passing it as a pointer for subtoken_node->subtoken
// So it will be freed in free_token_list.c instead
static t_subtoken_list	*get_subtoken_list(char *token)
{
	t_subtoken_list	*subtoken_list;
	t_subtoken_node	*subtoken_node;
	char			*subtoken;

	subtoken_list = create_subtoken_list();
	subtoken = get_next_subtoken(token);
	while (subtoken)
	{
		subtoken = expand_tilde(subtoken);
		subtoken = expand_env(subtoken);
		subtoken = expand_escaped(subtoken);
		subtoken_node = create_subtoken_node(subtoken);
		link_subtoken_node(subtoken_node, subtoken_list);
		subtoken = get_next_subtoken(NULL);
	}
	return (subtoken_list);
}

t_token_list	*get_token_list(char *input)
{
	t_token_list	*token_list;
	t_token_node	*token_node;
	char			*token;

	token_list = create_token_list();
	token = get_next_token(input);
	while (token)
	{
		token_node = create_token_node(get_subtoken_list(token));
		link_token_node(token_node, token_list);
		free(token);
		token = get_next_token(NULL);
	}
	return (token_list);
}
