/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_postfix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:33:20 by ychng             #+#    #+#             */
/*   Updated: 2024/03/15 02:46:38 by ychng            ###   ########.fr       */
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

void	run_execve(char **envp, t_subtoken_list *cmd_list)
{
	(void)envp;
	(void)cmd_list;
}

int	run_cmd(char **envp, t_subtoken_list *cmd_list)
{
	static t_subtoken_list	*params_list;

	if (ft_strcmp(cmd_list->head->subtoken, "echo") == 0)
		return (blt_echo(cmd_list->head->next));
	else if (ft_strcmp(cmd_list->head->subtoken, "pwd") == 0)
		return (blt_pwd());
	else if (ft_strcmp(cmd_list->head->subtoken, "export") == 0)
		return (blt_export(&envp, cmd_list->head->next, params_list));
	else if (ft_strcmp(cmd_list->head->subtoken, "unset") == 0)
		return (blt_unset(envp, params_list, cmd_list->head->next));
	else if (ft_strcmp(cmd_list->head->subtoken, "env") == 0)
		return (blt_env(envp));
	else if (ft_strcmp(cmd_list->head->subtoken, "exit") == 0)
		blt_exit(cmd_list->head->next);
	else
		run_execve(envp, cmd_list);
	return (-1);
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
		if (run_cmd(NULL, cmd_list) == 0)
			exit(0);
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
		if (run_cmd(NULL, cmd_list) == 0)
			exit(0);
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
	{
		if (wait(&last_exec_cmd_status) == -1)
		{
			printf("wait failed\n");
			exit(-1);
		}
	}
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
