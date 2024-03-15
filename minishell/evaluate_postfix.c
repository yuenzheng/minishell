/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_postfix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:33:20 by ychng             #+#    #+#             */
/*   Updated: 2024/03/15 18:25:28 by ychng            ###   ########.fr       */
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

void	free_double_array(char **double_array)
{
	int	i;

	i = -1;
	while (double_array[++i])
		free(double_array[i]);
	free(double_array);
}

void	handle_execve(char **envp, t_subtoken_list *cmd_list)
{
	char	**args;
	char	*bin;

	args = cmd_list_to_double_array(cmd_list);
	bin = find_full_bin_path(args[0], envp);
	if (bin == NULL)
	{
		printf("executable doesn't exist\n");
		exit(-1);
	}
	execve(bin, args, envp);
	free_double_array(args);
	exit(-1);
}

void	run_cmd(char **envp, t_subtoken_list *cmd_list)
{
	static t_subtoken_list	*args_history;
	char					*subtoken;
	t_subtoken_node			*args;

	subtoken = cmd_list->head->subtoken;
	args = cmd_list->head->next;
	if (ft_strcmp(subtoken, "echo") == 0)
		blt_echo(args);
	else if (ft_strcmp(subtoken, "pwd") == 0)
		blt_pwd();
	else if (ft_strcmp(subtoken, "export") == 0)
		blt_export(&envp, args, args_history);
	else if (ft_strcmp(subtoken, "unset") == 0)
		blt_unset(envp, args, args_history);
	else if (ft_strcmp(subtoken, "env") == 0)
		blt_env(envp);
	else if (ft_strcmp(subtoken, "exit") == 0)
		blt_exit(args);
	else
		handle_execve(envp, cmd_list);
}

void	exec_cmd(int pipe_fd[], int prev_pipe_fd[], t_subtoken_list *cmd_list)
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
		run_cmd(NULL, cmd_list);
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

void	exec_cmd_with_pipe(int prev_pipe_fd[], t_subtoken_list *cmd_list)
{
	int		pipe_fd[2];

	if(pipe(pipe_fd) == -1)
	{
		printf("pipe function failed\n");
		exit(-1);
	}
	exec_cmd(pipe_fd, prev_pipe_fd, cmd_list);
}

void	exec_last_cmd(int prev_pipe_fd[], t_subtoken_list *cmd_list)
{
	pid_t	pid;

	pid = create_fork();
	if (pid == 0)
	{
		if (prev_pipe_fd[0] != 0)
		{
			close(prev_pipe_fd[1]);
			dup2(prev_pipe_fd[0], STDIN_FILENO);
			close(prev_pipe_fd[0]);
		}
		run_cmd(NULL, cmd_list);
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

int	wait_for_forks(int exec_count)
{
	int	last_exec_cmd_status;

	last_exec_cmd_status = 0;
	while (exec_count--)
		waitpid(-1, &last_exec_cmd_status, 0);
	return (WEXITSTATUS(last_exec_cmd_status));
}

bool	operand_succeed(t_token_node *operand)
{
	int				exec_count;
	int				prev_pipe_fd[2];
	t_subtoken_list	*subtoken_list;
	t_subtoken_list	*cmd_list;

	exec_count = 0;
	ft_bzero(prev_pipe_fd, sizeof(int) * 2);
	subtoken_list = operand->subtoken_list;
	while (subtoken_list->head)
	{
		cmd_list = create_subtoken_list();
		while (subtoken_list->head && !is_pipe(*subtoken_list->head->subtoken))
			link_subtoken_list(pop_subtoken_list_head(subtoken_list), cmd_list);
		if (subtoken_list->head)
		{
			exec_cmd_with_pipe(prev_pipe_fd, cmd_list);
			free_subtoken_node(pop_subtoken_list_head(subtoken_list));
		}
		else
			exec_last_cmd(prev_pipe_fd, cmd_list);
		exec_count++;
	}
	printf("status %d\n", wait_for_forks(exec_count));
	return (true);
}

void	process_expression(t_token_list *postfix, t_token_list *stack)
{
	t_token_node	*operator;
	t_token_node	*loperand;
	t_token_node	*roperand;

	operator = pop_token_list_head(postfix);
	roperand = pop_token_list_tail(stack);
	loperand = pop_token_list_tail(stack);
	(void)roperand;
	if (ft_strcmp(first_subtoken(operator), "||") == 0)
	{
		// t_token_node	*result;
		
		// if (operand_succeed(loperand))
		// 	result = loperand;
		// else if (operand_succeed(roperand))
		// 	result = roperand;
		// link_token_list(result, stack);
		operand_succeed(loperand);
	}
}

void	evaluate_postfix(t_token_list *postfix)
{
	t_token_list	stack;

	stack = (t_token_list){0};
	while (postfix->head)
	{
		if (is_logical_operator(first_subtoken(postfix->head)))
		{
			process_expression(postfix, &stack);
			free_token_node(pop_token_list_head(postfix));
		}
		else
			link_token_list(pop_token_list_head(postfix), &stack);
	}
}
