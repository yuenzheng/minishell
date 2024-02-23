/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:28:13 by ychng             #+#    #+#             */
/*   Updated: 2024/02/23 14:44:24 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*get_directory(char *user)
{
	char	*directory;
	char	*home_directory;

	home_directory = getenv("HOME");
	if (*user == '\0')
		return (ft_strdup(home_directory));
	user = extract_until_delim(user, " /\\");
	directory = find_user_directory(user);
	free(user);
	return (directory);
}

static char	*expand_tilde_in_token(char *directory, char *token)
{
	char	*result;
	int		joined_len;

	if (directory)
		token += ft_strcspn(token, " /\\");
	joined_len = ft_strlen(directory) + ft_strlen(token);
	result = malloc(sizeof(char) * (joined_len + 1));
	if (!result)
	{
		printf("malloc failed for result\n");
		exit(-1);
	}
	*result = '\0';
	ft_strcpy(result, directory);
	ft_strcat(result, token);
	free(directory);
	return (result);
}

char	*expand_tilde(char *token)
{
	char	*directory;
	char	*result;

	if (is_tilde(*token))
	{
		directory = get_directory(token + 1);
		result = expand_tilde_in_token(directory, token);
		return (result);
	}
	return (token);
}
