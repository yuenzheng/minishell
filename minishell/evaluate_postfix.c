/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_postfix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:33:20 by ychng             #+#    #+#             */
/*   Updated: 2024/03/27 01:13:29 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

pid_t	create_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("fork failed for pid\n");
		exit(-1);
	}
	return (pid);
}

char	**cmd_list_to_double_array(t_subtokenlist *cmd_list)
{
	char			**result;
	t_subtokennode	*current;
	int				i;

	result = malloc(sizeof(char *) * (count_subtokenlist(cmd_list) + 1));
	if (result == NULL)
	{
		printf("malloc failed for result\n");
		exit(-1);
	}
	i = 0;
	current = cmd_list->head;
	while (current)
	{
		result[i] = ft_strdup(current->subtoken);
		if (result[i] == NULL)
		{
			printf("ft_strdup failed for result[%d]\n", i);
			exit(-1);
		}
		i++;
		current = current->next;
	}
	result[i] = NULL;
	return (result);
}

char	*find_full_bin_path(char *bin, char **envp)
{
	int		i;
	char	*path;
	char	*full_path;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) != 0)
			continue ;
		path = ft_strtok(envp[i] + 5, ":");
		while (path)
		{
			full_path = ft_strjoin(path, bin, "/");
			if (access(full_path, F_OK) == 0)
				return (full_path);
			free(full_path);
			path = ft_strtok(NULL, ":");
		}
	}
	return (NULL);
}

int	run_execve(char **envp, t_subtokenlist *cmd_list)
{
	char	**args;
	char	*bin;

	args = cmd_list_to_double_array(cmd_list);
	bin = find_full_bin_path(args[0], envp);
	if (bin == NULL)
	{
		printf("executable doesn't exist\n");
		return (-1);
	}
	execve(bin, args, envp);
	free_double_array(args);
	return (-1);
}

int	run_cmd(char ***envp, t_subtokenlist *cmd_list)
{
	t_subtokennode			*args;
	char					*cmd;

	args = cmd_list->head->next;
	cmd = cmd_list->head->subtoken;
	if (!ft_strcmp(cmd, "echo"))
		return (blt_echo(args));
	if (!ft_strcmp(cmd, "cd"))
		return (blt_cd(*envp, args));
	if (!ft_strcmp(cmd, "pwd"))
		return (blt_pwd());
	if (!ft_strcmp(cmd, "export"))
		return (blt_export(envp, args));
	if (!ft_strcmp(cmd, "unset"))
		return (blt_unset(*envp, args));
	if (!ft_strcmp(cmd, "env"))
		return (blt_env(*envp));
	if (!ft_strcmp(cmd, "exit"))
		return (blt_exit(args));
	return (run_execve(*envp, cmd_list));
}

void	handle_pipe_cmd(char ***envp, int pipe_fd[], int prev_pipe_fd[], \
			t_subtokenlist *cmd_list)
{
	pid_t	pid;

	pid = create_fork();
	if (pid == 0)
	{
		if (prev_pipe_fd[0] != 0)
		{
			close (prev_pipe_fd[1]);
			dup2(prev_pipe_fd[0], STDIN_FILENO);
			close(prev_pipe_fd[0]);
		}
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exit(run_cmd(envp, cmd_list));
	}
	else
	{
		if (prev_pipe_fd[0] != 0)
		{
			close(prev_pipe_fd[0]);
			close(prev_pipe_fd[1]);
		}
		prev_pipe_fd[0] = pipe_fd[0];
		prev_pipe_fd[1] = pipe_fd[1];
	}
}

void	update_exit_status(char **envp, int exit_status)
{
	char	*env_name;
	char	*exit_code;

	while (*envp)
	{
		if (is_question_mark(**envp) && is_equal(*(*envp + 1)))
		{
			env_name = ft_strndup(*envp, ft_strcspn(*envp, "=") + 1);
			if (!env_name)
			{
				printf("ft_strndup failed for env_name\n");
				exit(-1);
			}
			exit_code = ft_itoa(exit_status);
			if (!exit_code)
			{
				printf("ft_itoa failed for exit_code\n");
				exit(-1);
			}
			free(*envp);
			*envp = custom_strjoin(env_name, exit_code);
			free(exit_code);
		}
		envp++;
	}
}

void	handle_last_cmd(char ***envp, int prev_pipe_fd[], \
			t_subtokenlist *cmd_list)
{
	pid_t	pid;

	if (prev_pipe_fd[0] == 0)
		update_exit_status(*envp, run_cmd(envp, cmd_list));
	else
	{
		pid = create_fork();
		if (pid == 0)
		{
			if (prev_pipe_fd[0] != 0)
			{
				close(prev_pipe_fd[1]);
				dup2(prev_pipe_fd[0], STDIN_FILENO);
				close(prev_pipe_fd[0]);
			}
			exit(run_cmd(envp, cmd_list));
		}
		else
		{
			if (prev_pipe_fd[0] != 0)
			{
				close(prev_pipe_fd[0]);
				close(prev_pipe_fd[1]);
			}
		}
	}
}

void	exec_cmd(char ***envp, int prev_pipe_fd[], \
			t_subtokenlist *cmd_list, bool is_last_cmd)
{
	int	pipe_fd[2];

	if (!is_last_cmd)
	{
		if (pipe(pipe_fd) == -1)
		{
			printf("pipe failed for pipe_fd\n");
			exit(-1);
		}
		handle_pipe_cmd(envp, pipe_fd, prev_pipe_fd, cmd_list);
	}
	else
		handle_last_cmd(envp, prev_pipe_fd, cmd_list);
}

void	wait_for_forks(char **envp)
{
	int	exit_status;

	while (waitpid(-1, &exit_status, 0) > 0)
		update_exit_status(envp, WEXITSTATUS(exit_status));
}

bool	operand_succeed(char ***envp, t_tokennode *operand)
{
	int				prev_pipe_fd[2];
	t_subtokenlist	*subtokenlist;
	t_subtokenlist	*cmd_list;

	ft_bzero(prev_pipe_fd, sizeof(int) * 2);
	subtokenlist = operand->subtokenlist;
	while (subtokenlist->head)
	{
		cmd_list = create_subtokenlist();
		while (subtokenlist->head && !is_pipe(*subtokenlist->head->subtoken))
			link_subtokenlist(pop_subtokenlist_head(subtokenlist), cmd_list);
		// if (subtokenlist->head)
		// {
		// 	exec_cmd_with_pipe(envp, prev_pipe_fd, cmd_list);
		// }
		// else
		// 	exec_last_cmd(envp, prev_pipe_fd, cmd_list);
		exec_cmd(envp, prev_pipe_fd, cmd_list, !subtokenlist->head);
		if (subtokenlist->head)
			free_subtokennode(pop_subtokenlist_head(subtokenlist));
		free_subtokenlist(cmd_list);
	}
	wait_for_forks(*envp);
	return (true);
}

void	process_expression(char ***envp, t_tokenlist *postfix, \
			t_tokenlist *stack)
{
	t_tokennode	*operator;
	t_tokennode	*loperand;
	t_tokennode	*roperand;

	operator = pop_tokenlist_head(postfix);
	roperand = pop_tokenlist_tail(stack);
	loperand = pop_tokenlist_tail(stack);
	if (ft_strcmp(first_subtoken(operator), "||") == 0)
	{
		// t_tokennode	*result;

		// if (operand_succeed(loperand))
		// 	result = loperand;
		// else if (operand_succeed(roperand))
		// 	result = roperand;
		// link_tokenlist(result, stack);
		operand_succeed(envp, loperand);
	}
	free_tokennode(operator);
	free_tokennode(roperand);
	free_tokennode(loperand);
}

void	evaluate_postfix(char ***envp, t_tokenlist *postfix)
{
	t_tokenlist	stack;

	stack = (t_tokenlist){0};
	while (postfix->head)
	{
		if (is_logicalop(first_subtoken(postfix->head)))
		{
			process_expression(envp, postfix, &stack);
			free_tokennode(pop_tokenlist_head(postfix));
		}
		else
		{
			link_tokenlist(pop_tokenlist_head(postfix), &stack);
			// Need to free expression if it's alone without logical operator
		}
	}
	free_tokennode(stack.head);
}
