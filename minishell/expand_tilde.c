/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:28:13 by ychng             #+#    #+#             */
/*   Updated: 2024/02/23 04:19:59 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_tilde(char c)
{
	return (c == '~');
}

bool	is_forwardslash(char c)
{
	return (c == '/');
}

int	open_passwd_file(void)
{
	int	fd;

	fd = open("/etc/passwd", O_RDONLY);
	if (fd == -1)
	{
		printf("open failed for fd\n");
		exit(-1);
	}
	return (fd);
}

char	*find_directory(char *line, char *user)
{
	char	*field;
	int		field_column;

	field = ft_strtok(line, ":");
	if (field && ft_strcmp(line, user) != 0)
		return (NULL);
	field_column = 5;
	while (field_column--)
		field = ft_strtok(NULL, ":");
	return (ft_strdup(field));
}

char	*find_user_directory(char *user)
{
	int		fd;
	char	*line;
	char	*directory;

	fd = open_passwd_file();
	line = get_next_line(fd);
	while (line)
	{
		directory = find_directory(line, user);
		if (directory != NULL)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	return (directory);	
}

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\n');
}

char	*extract_until_delim(char *user, char *delim)
{
	int	user_len;

	user_len = ft_strcspn(user, delim);
	if (is_backslash(user[user_len]) && !is_whitespace(user[user_len + 1]))
		user_len++;
	return (ft_strndup(user, user_len));
}

char	*get_directory(char *user)
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

char	*expand_tilde_in_token(char *directory, char *token)
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
	return (NULL);
}
