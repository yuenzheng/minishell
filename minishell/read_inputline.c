/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:39:08 by ychng             #+#    #+#             */
/*   Updated: 2024/03/27 08:52:19 by ychng            ###   ########.fr       */
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

bool	has_noerror(char *input)
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

int	dup_stdoutfd(char *input)
{
	int	stdoutfd;

	stdoutfd = dup(STDOUT_FILENO);
	if (stdoutfd == -1)
	{
		printf("dup failed for stdoutfd\n");
		free(input);
		exit(-1);
	}
	return (stdoutfd);
}

int	dup_nullfd(char *input)
{
	int	nullfd;

	nullfd = open("/dev/null", O_WRONLY);
	if (nullfd == -1)
	{
		printf("open failed for nullfd\n");
		free(input);
		exit(-1);
	}
	return (nullfd);
}

char	*extract_heredoc(char *input, int joinedlen)
{
	char	*joinedtokens;
	char	*subtoken;
	char	*result;

	joinedtokens = ft_strndup(input, joinedlen);
	if (!joinedtokens)
	{
		printf("ft_strndup failed for joinedtokens\n");
		free(input);
		exit(-1);
	}
	subtoken = get_next_subtoken(joinedtokens);
	while (subtoken)
	{
		if (is_heredoc(subtoken))
		{
			result = custom_strjoin(result, subtoken);
			// i was planning to just joined each heredoc with their name
			// problem im facing
			// what if no name exist or name is an error
			// <<, << ||, << (.
		}
		subtoken = get_next_subtoken(NULL);
	}
	return (ft_strndup(input, joinedlen));
}

char	*trim_errorpart(char *input)
{
	int		openlogicalops;
	int		openbrackets;
	int		joinedlen;
	char	*token;

	openlogicalops = 0;
	openbrackets = 0;
	joinedlen = 0;
	token = get_next_token(input, false);
	while (token)
	{
		if (has_logicaloperr(token, &openlogicalops) \
			|| has_bracketerr(token, &openbrackets))
		{
			joinedlen += ft_strlen(token);
			free(token);
			break ;
		}
		joinedlen += ft_strlen(token);
		free(token);
		token = get_next_token(NULL, false);
	}
	return (extract_heredoc(input, joinedlen));
}


// Lazy to write another function
// So I tried a different method
// Which is to redirect to /dev/null
// Because has_noerror will print to stdout
char	*handle_errortrim(char *input)
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
	while (has_noerror(input) && has_openblock(input))
	{
		update_history(input);
		input = closequotes(input);
		input = closebrackets(input);
		input = closelogicalops(input);
	}
	update_history(input);
	input = handle_errortrim(input);
	printf("%s\n", input);
	return (input);
}
