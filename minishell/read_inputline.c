/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:39:08 by ychng             #+#    #+#             */
/*   Updated: 2024/03/27 06:49:45 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*handle_maininput(void)
{
	bool	firstiter;
	char	*maininput;

	firstiter = true;
	maininput = NULL;
	while (firstiter || *maininput == '\0')
	{
		free(maininput);
		firstiter = false;
		maininput = readline("main> ");
		if (maininput == NULL)
		{
			printf("Ctrl+D was pressed in handle_maininput\n");
			exit(-1);
		}
	}
	return (maininput);
}

bool	has_no_error(char *input)
{
	int		openlogicalops;
	int		openbrackets;
	char	*token;

	openlogicalops = 0;
	openbrackets = 0;
	token = get_next_token(input, false);
	while (token)
	{
		if (has_logicaloperr(token, &openlogicalops) \
			|| has_bracketerr(token, &openbrackets))
		{
			free(token);
			return (false);
		}
		free(token);
		token = get_next_token(NULL, false);
	}
	return (true);
}

// order don't matter
bool	has_openblock(char *input)
{
	return (has_openquotes(input) \
		|| (has_openbrackets(input)) \
		|| (has_openlogicalops(input)));
}

char	*read_inputline(void)
{
	char	*input;

	input = handle_maininput();
	while (has_no_error(input) && has_openblock(input))
	{
		update_history(input);
		input = closequotes(input);
		input = closebrackets(input);
		input = closelogicalops(input);
	}
	update_history(input);
	// printf("%s\n", input);
	return (input);
}
