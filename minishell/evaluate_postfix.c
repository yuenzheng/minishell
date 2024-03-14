/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_postfix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:33:20 by ychng             #+#    #+#             */
/*   Updated: 2024/03/15 01:30:53 by ychng            ###   ########.fr       */
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

void	exec_cmd(int pipe_fd[], int prev_pipe_fd[], t_token_list *cmd_list)
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
		return (blt_echo(cmd_list->head->next));
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

void	exec_cmd_with_pipe(int prev_pipe_fd[], t_token_list *cmd_list)
{
	int		pipe_fd[2];

	if(pipe(pipe_fd) == -1)
	{
		printf("pipe function failed\n");
		exit(-1);
	}
	exec_cmd(pipe_fd, prev_pipe_fd, cmd_list);
}

void	exec_last_cmd(int prev_pipe_fd[], t_token_list *cmd_list)
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
		return (blt_echo(cmd_list->head->next));
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

void	wait_for_forks(int exec_count)
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
		while (subtoken_list->head && !is_pipe(subtoken_list->head->subtoken))
			link_subtoken_list(pop_subtoken_list(subtoken_list), cmd_list);
		if (subtoken_list->head)
			exec_cmd_with_pipe(prev_pipe_fd, cmd_list);
		else
			exec_last_cmd(prev_pipe_fd, cmd_list);
		exec_count++;
	}
	wait_for_forks(exec_count);
	return (true);
}

void	process_expression(t_token_list *postfix, t_token_list *stack)
{
	t_token_node	*operator;
	t_token_node	*loperand;
	t_token_node	*roperand;

	operator = pop_token_list_head(postfix);
	loperand = pop_token_list_tail(stack);
	roperand = pop_token_list_tail(stack);
	if (ft_strcmp(operator, "||") == 0)
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
			process_expression(postfix, &stack);
		else
			link_token_list(pop_token_list_head(postfix), &stack);
	}
}
