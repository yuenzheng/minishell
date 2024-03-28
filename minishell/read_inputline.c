/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:39:08 by ychng             #+#    #+#             */
/*   Updated: 2024/03/28 23:57:06 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*handle_maininput(void)
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

int	redirlen(char *token)
{
	if (ft_strncmp(token, "<<<", 3) == 0)
		return (3);
	if (ft_strncmp(token, "<<", 2) == 0
		|| (ft_strncmp(token, ">>", 2) == 0))
		return (2);
	if (ft_strncmp(token, "<", 1) == 0
		|| (ft_strncmp(token, ">", 1) == 0)
		|| (ft_strncmp(token, "|", 1) == 0))
		return (1);
	return (0);
}

bool	is_notvalidname(char *token)
{
	char	*subtoken;

	if (is_redirection_n(token))
	{
		subtoken = get_next_subtoken(token);
		printf("syntax error near unexpected token `%s'\n", subtoken);
		free(subtoken);
		return (true);
	}
	return (false);
}



static bool	has_noerror(char *input)
{
	int		openlogicalops;
	int		openbrackets;
	int		openredirs;
	char	*token;

	openlogicalops = 0;
	openbrackets = 0;
	openredirs = 0;
	token = get_next_token(input, false);
	while (token)
	{
		if (has_logicaloperr(token, &openlogicalops) \
			|| has_bracketerr(token, &openbrackets) \
			|| has_redirerr(token, &openredirs))
		{
			free(token);
			return (false);
		}
		free(token);
		token = get_next_token(NULL, false);
	}
	if (openredirs > 0)
	{
		printf("syntax error near unexpected `newline'\n");
		return (false);
	}
	return (true);
}

// order don't matter
static bool	has_openblock(char *input)
{
	return (has_openquotes(input) \
		|| (has_openbrackets(input)) \
		|| (has_openlogicalops(input)));
}





// Lazy to write another function
// So I tried a different method
// Which is to redirect to /dev/null
// Because has_noerror will print to stdout
static char	*handle_errortrim(char *input)
{
	int	original_stdout;
	int	null_fd;

	original_stdout = dup_stdoutfd(input);
	null_fd = dup_nullfd(input);
	dup2(null_fd, STDOUT_FILENO);
	if (!has_noerror(input))
		input = trim_errorpart(input);
	dup2(original_stdout, STDOUT_FILENO);
	close(null_fd);
	close(original_stdout);
	return (input);
}

char	*read_inputline(void)
{
	char	*input;

	input = handle_maininput();
	update_history(input);
	while (has_noerror(input) && has_openblock(input))
	{
		input = closequotes(input);
		if (!has_noerror(input))
			break ;
		input = closebrackets(input);
		if (!has_noerror(input))
			break ;
		input = closelogicalops(input);
		update_history(input);
	}
	input = handle_errortrim(input);
	printf("%s\n", input);
	return (input);
}
