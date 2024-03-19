/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_postfix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:33:20 by ychng             #+#    #+#             */
/*   Updated: 2024/03/19 18:46:16 by ychng            ###   ########.fr       */
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

char	**cmd_list_to_double_array(t_subtoken_list *cmd_list)
{
	char			**result;
	t_subtoken_node	*current;
	int				i;

	result = malloc(sizeof(char *) * (count_subtoken_list(cmd_list) + 1));
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

int	run_execve(char **envp, t_subtoken_list *cmd_list)
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

int	run_cmd(char ***envp, t_subtoken_list *cmd_list)
{
	t_subtoken_node			*args;
	char					*cmd;

	args = cmd_list->head->next;
	cmd = cmd_list->head->subtoken;
	if (!ft_strcmp(cmd, "echo"))
		return (blt_echo(args));
	if (!ft_strcmp(cmd, "cd"))
		return (-1);
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
			t_subtoken_list *cmd_list)
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

void	handle_last_cmd(char ***envp, int prev_pipe_fd[], t_subtoken_list *cmd_list)
{
	pid_t	pid;

	if (prev_pipe_fd[0] == 0)
		run_cmd(envp, cmd_list);
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
			t_subtoken_list *cmd_list, bool is_last_cmd)
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

int	wait_for_forks(void)
{
	int	last_exec_cmd_status;

	last_exec_cmd_status = 0;
	while (waitpid(-1, &last_exec_cmd_status, 0) > 0)
		;
	return (WEXITSTATUS(last_exec_cmd_status));
}

bool	operand_succeed(char ***envp, t_token_node *operand)
{
	int				prev_pipe_fd[2];
	t_subtoken_list	*subtoken_list;
	t_subtoken_list	*cmd_list;

	ft_bzero(prev_pipe_fd, sizeof(int) * 2);
	subtoken_list = operand->subtoken_list;
	while (subtoken_list->head)
	{
		cmd_list = create_subtoken_list();
		while (subtoken_list->head && !is_pipe(*subtoken_list->head->subtoken))
			link_subtoken_list(pop_subtoken_list_head(subtoken_list), cmd_list);
		// if (subtoken_list->head)
		// {
		// 	exec_cmd_with_pipe(envp, prev_pipe_fd, cmd_list);
		// }
		// else
		// 	exec_last_cmd(envp, prev_pipe_fd, cmd_list);
		exec_cmd(envp, prev_pipe_fd, cmd_list, !subtoken_list->head);
		if (subtoken_list->head)
			free_subtoken_node(pop_subtoken_list_head(subtoken_list));
		free_subtoken_list(cmd_list);
	}
	wait_for_forks();
	return (true);
}

void	process_expression(char ***envp, t_token_list *postfix, \
			t_token_list *stack)
{
	t_token_node	*operator;
	t_token_node	*loperand;
	t_token_node	*roperand;

	operator = pop_token_list_head(postfix);
	roperand = pop_token_list_tail(stack);
	loperand = pop_token_list_tail(stack);
	if (ft_strcmp(first_subtoken(operator), "||") == 0)
	{
		// t_token_node	*result;

		// if (operand_succeed(loperand))
		// 	result = loperand;
		// else if (operand_succeed(roperand))
		// 	result = roperand;
		// link_token_list(result, stack);
		operand_succeed(envp, loperand);
	}
	free_token_node(operator);
	free_token_node(roperand);
	free_token_node(loperand);
}

void	evaluate_postfix(char ***envp, t_token_list *postfix)
{
	t_token_list	stack;

	stack = (t_token_list){0};
	while (postfix->head)
	{
		if (is_logical_operator(first_subtoken(postfix->head)))
		{
			process_expression(envp, postfix, &stack);
			free_token_node(pop_token_list_head(postfix));
		}
		else
		{
			link_token_list(pop_token_list_head(postfix), &stack);
			// Need to free expression if it's alone without logical operator
		}
	}
	free_token_node(stack.head);
}
