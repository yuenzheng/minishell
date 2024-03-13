/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:28:13 by ychng             #+#    #+#             */
/*   Updated: 2024/03/13 11:43:02 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*get_directory_from_env(char *user)
{
	char	*home_directory;

	user = extract_until_delim(user, " /\\");
	if (*user == '\0')
	{
		free(user);
		home_directory = getenv("HOME");
		return (ft_strdup(home_directory));
	}
	free(user);
	return (NULL);
}

static char	*get_directory_from_passwd(char *user)
{
	char	*user_directory;

	user = extract_until_delim(user, " /\\");
	user_directory = find_user_directory(user);
	free(user);
	return (user_directory);
}

static char	*get_directory_from_users(char *user)
{
	char			*home_directory;
	DIR				*users_directory;
	struct dirent	*entry;

	user = extract_until_delim(user, " /\\");
	home_directory = NULL;
	users_directory = open_users_directory();
	if (!users_directory)
	{
		free(user);
		return (NULL);
	}
	entry = readdir(users_directory);
	while (entry)
	{
		home_directory = find_home_directory(entry->d_name, user);
		if (home_directory != NULL)
			break ;
		entry = readdir(users_directory);
	}
	closedir(users_directory);
	free(user);
	return (home_directory);
}

static char	*expand_tilde_in_subtoken(char *directory, char *subtoken)
{
	char	*result;
	int		joined_len;

	if (directory)
		subtoken += ft_strcspn(subtoken, " /\\");
	joined_len = ft_strlen(directory) + ft_strlen(subtoken);
	result = malloc(sizeof(char) * (joined_len + 1));
	if (!result)
	{
		printf("malloc failed for result\n");
		exit(-1);
	}
	*result = '\0';
	ft_strcpy(result, directory);
	ft_strcat(result, subtoken);
	free(directory);
	return (result);
}

char	*expand_tilde(char *subtoken)
{
	char	*directory;
	char	*result;

	directory = NULL;
	if (is_tilde(*subtoken))
	{
		if (directory == NULL)
			directory = get_directory_from_env(subtoken + 1);
		if (directory == NULL)
			directory = get_directory_from_passwd(subtoken + 1);
		if (directory == NULL)
			directory = get_directory_from_users(subtoken + 1);
		result = expand_tilde_in_subtoken(directory, subtoken);
		free(subtoken);
		return (result);
	}
	return (subtoken);
}
