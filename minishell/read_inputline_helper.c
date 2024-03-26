/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:20:21 by ychng             #+#    #+#             */
/*   Updated: 2024/03/27 01:45:31 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*closequotes(char *input)
{
	char	*joininput;

	if (has_openquotes(input))
		input = custom_strjoin(input, "\n");
	while (has_openquotes(input))
	{
		joininput = readline("join> ");
		if (!joininput)
		{
			printf("Ctrl+D was pressed in closequotes\n");
			free(input);
			exit(-1);
		}
		joininput = format_joininput(joininput);
		input = custom_strjoin(input, joininput);
		free(joininput);
	}
	return (input);
}

char	*closebrackets(char *input)
{
	char	*joininput;
	char	*triminput;

	joininput = readline("join> ");
	if (joininput == NULL)
	{
		printf("Ctrl+D was pressed in closebrackets\n");
		free(input);
		exit(-1);
	}
	triminput = ft_strtrim(input, "\n");
	free(input);
	input = triminput;
	if (*joininput != '\0')
		input = custom_strjoin(input, " ");
	input = custom_strjoin(input, joininput);
	input = closequotes(input);
	free(joininput);
	return (input);
}

char	*closelogicalops(char *input)
{
	char	*joininput;

	while (has_openlogicalops(input) == true)
	{
		joininput = readline("join> ");
		if (joininput == false)
		{
			printf("Ctrl+D was pressed in closelogicalops\n");
			free(input);
			exit(-1);
		}
		input = custom_strjoin(input, " ");
		input = custom_strjoin(input, joininput);
		free(joininput);
	}
	return (input);
}

void	update_history(char *input)
{
	static char	*previnput;

	if (previnput && !ft_strcmp(previnput, input) && !contains_newline(input))
		return ;
	if (previnput != NULL)
		free(previnput);
	previnput = ft_strdup(input);
	if (!previnput)
	{
		printf("ft_strdup failed for previnput\n");
		exit(-1);
	}
	add_history(previnput);
}
