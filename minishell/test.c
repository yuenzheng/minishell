/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:50:35 by ychng             #+#    #+#             */
/*   Updated: 2024/02/12 18:38:08 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_node	*create_node(char *token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
	{
		printf("malloc failed for node\n");
		exit(-1);
	}
	node->token = token;
	node->next = NULL;
	return (node);
}

void	push_node(t_stack *stack, t_node *node)
{
	if (stack == NULL || node == NULL)
		return ;
	if (stack->head == NULL)
	{
		stack->head = node;
		stack->tail = node;
	}
	else
	{
		stack->tail->next = node;
		stack->tail = node;
	}
}

t_node	*pop_node(t_stack *stack)
{
	t_node	*last_node;
	t_node	*current;

	if (stack == NULL || stack->head == NULL)
		return (NULL);
	last_node = stack->tail;
	if (stack->head == stack->tail)
	{
		stack->head = NULL;
		stack->tail = NULL;
		return (last_node);
	}
	current = stack->head;
	while (current->next != NULL)
	{
		stack->tail = current;
		current = current->next;
	}
	stack->tail->next = NULL;
	return (last_node);
}

bool	is_number(char *token)
{
	int	i;

	i = -1;
	while (token[++i])
	{
		if (!(token[i] >= '0' && token[i] <= '9'))
			return (false);
	}
	return (true);
}

bool	is_operator(char *token)
{
	char	op_char;

	if (ft_strcmp(token, "+") == 0)
		return (true);
	else if (ft_strcmp(token, "-") == 0)
		return (true);
	else if (ft_strcmp(token, "*") == 0)
		return (true);
	else if (ft_strcmp(token, "/") == 0)
		return (true);
	else if (ft_strcmp(token, "%") == 0)
		return (true);
	else if (ft_strcmp(token, "**") == 0)
		return (true);
	return (false);
}

int	precedence(char *token)
{
	if (ft_strcmp(token, "+") == 0)
		return (1);
	else if (ft_strcmp(token, "-") == 0)
		return (1);
	else if (ft_strcmp(token, "*") == 0)
		return (2);
	else if (ft_strcmp(token, "/") == 0)
		return (2);
	else if (ft_strcmp(token, "%") == 0)
		return (2);
	else if (ft_strcmp(token, "**") == 0)
		return (3);
	return (-1);
}

void	process_number_token(char *token, t_stack *postfix)
{
	push_node(postfix, create_node(token));
}

void	process_operator_token(
	char *token, t_stack *postfix, t_stack *opstack)
{
	t_node	*top;

	top = opstack->tail;
	while (top && precedence(top->token) >= precedence(token))
		push_node(postfix, pop_node(opstack));
	push_node(opstack, create_node(token));
}

void	process_left_parenthesis_token(char *token, t_stack *opstack)
{
	push_node(opstack, create_node(token));
}

void	process_right_parenthesis_token(
	char *token, t_stack *postfix, t_stack *opstack)
{
	while (opstack->tail && ft_strcmp(opstack->tail->token, "(") != 0)
		push_node(postfix, pop_node(opstack));
	free(pop_node(opstack));
}

// {"91", "+", "23", "*", "(", }
void	process_infix_token(char *token, t_stack *postfix, t_stack *opstack)
{
	if (is_number(token))
		process_number_token(token, postfix);
	else if (is_operator(token))
		process_operator_token(token, postfix, opstack);
	else if (ft_strcmp(token, "(") == 0)
		process_left_parenthesis_token(token, opstack);
	else if (ft_strcmp(token, ")") == 0)
		process_right_parenthesis_token(token, postfix, opstack);
}

void	to_postfix(char **tokens)
{
	t_stack	postfix;
	t_stack	opstack;
	int		i;

	postfix = (t_stack){0};
	opstack = (t_stack){0};
	i = -1;
	while (tokens[++i])
		process_infix_token(tokens[i], &postfix, &opstack);
	while (opstack.tail != NULL)
		push_node(&postfix, pop_node(&opstack));
	t_node	*temp;

	temp = postfix.head;
	while (temp != NULL)
	{
		printf("%s\n", temp->token);
		temp = temp->next;
	}
}

int main(void)
{
	char *postfixExpr[] = { "2","+","(","3","*","(","8","-","4",")",")", NULL };
	to_postfix(postfixExpr);
}
