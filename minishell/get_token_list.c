/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:44:19 by ychng             #+#    #+#             */
/*   Updated: 2024/03/19 19:28:29 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Don't need to free subtoken in here,
// Becase i'm passing it as a pointer for subtoken_node->subtoken
// So it will be freed in free_token_list.c instead
static t_subtoken_list	*get_subtoken_list(char *token, char **envp)
{
	t_subtoken_list	*subtoken_list;
	char			*subtoken;
	bool			expand_heredoc;

	subtoken_list = create_subtoken_list();
	if (is_logical_operator(token))
	{
		subtoken = ft_strdup(token);
		link_subtoken_list(create_subtoken_node(subtoken), subtoken_list);
	}
	else
	{
		subtoken = get_next_subtoken(token);
		expand_heredoc = false;
		while (subtoken)
		{
			subtoken = expand_subtoken(subtoken, expand_heredoc, envp);
			if (is_heredoc(subtoken) || expand_heredoc == true)
				expand_heredoc = !expand_heredoc;
			link_subtoken_list(create_subtoken_node(subtoken), subtoken_list);
			subtoken = get_next_subtoken(NULL);
		}
	}
	return (subtoken_list);
}

t_token_list	*get_token_list(char *input, char **envp)
{
	t_token_list	*token_list;
	t_token_node	*token_node;
	char			*token;

	token_list = create_token_list();
	token = get_next_token(input);
	while (token)
	{
		if (ft_strspn(token, " ") != ft_strlen(token))
		{
			token_node = create_token_node(get_subtoken_list(token, envp));
			link_token_list(token_node, token_list);
		}
		free(token);
		token = get_next_token(NULL);
	}
	return (token_list);
}
