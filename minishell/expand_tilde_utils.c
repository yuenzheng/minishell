/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:39:27 by ychng             #+#    #+#             */
/*   Updated: 2024/02/23 14:43:33 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*extract_until_delim(char *user, char *delim)
{
	int	user_len;

	user_len = ft_strcspn(user, delim);
	if (is_backslash(user[user_len]) && !is_newline(user[user_len + 1]))
		user_len++;
	return (ft_strndup(user, user_len));
}

static int	open_passwd_file(void)
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

static char	*find_directory(char *line, char *user)
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
