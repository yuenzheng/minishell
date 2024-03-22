/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:50:35 by ychng             #+#    #+#             */
/*   Updated: 2024/03/23 01:07:07 by ychng            ###   ########.fr       */
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
	node->prev = NULL;
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
		node->next = stack->head;
		stack->head->prev = node;
		stack->head = node;
	}
}

t_node	*popnode(t_stack *stack)
{
	t_node	*top_node;

	if (stack == NULL || stack->head == NULL)
		return (NULL);
	top_node = stack->head;
	if (stack->head == stack->tail)
	{
		stack->head = NULL;
		stack->tail = NULL;
		return (top_node);
	}
	stack->head = stack->head->next;
	stack->head->prev = NULL;
	top_node->next = NULL;
	return (top_node);
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

	if (ft_strcmp(token, "|") == 0)
		return (true);
	else if (ft_strcmp(token, "^") == 0)
		return (true);
	else if (ft_strcmp(token, "&") == 0)
		return (true);
	else if (ft_strcmp(token, "+") == 0)
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
	if (ft_strcmp(token, "|") == 0)
		return (0);
	else if (ft_strcmp(token, "^") == 0)
		return (1);
	else if (ft_strcmp(token, "&") == 0)
		return (2);
	else if (ft_strcmp(token, "+") == 0)
		return (3);
	else if (ft_strcmp(token, "-") == 0)
		return (3);
	else if (ft_strcmp(token, "*") == 0)
		return (4);
	else if (ft_strcmp(token, "/") == 0)
		return (4);
	else if (ft_strcmp(token, "%") == 0)
		return (4);
	else if (ft_strcmp(token, "**") == 0)
		return (5);
	return (-1);
}

void	process_number_token(char *token, t_stack *postfix)
{
	push_node(postfix, create_node(token));
}

void	process_operator_token(
	char *token, t_stack *postfix, t_stack *opstack)
{
	t_node	*top_node;

	top_node = opstack->head;
	while (top_node && precedence(top_node->token) >= precedence(token))
	{
		push_node(postfix, popnode(opstack));
		top_node = opstack->head;
	}
	push_node(opstack, create_node(token));
}

void	process_left_parenthesis_token(char *token, t_stack *opstack)
{
	push_node(opstack, create_node(token));
}

void	process_right_parenthesis_token(
	char *token, t_stack *postfix, t_stack *opstack)
{
	t_node	*top_node;

	top_node = opstack->head;
	while (top_node && ft_strcmp(top_node->token, "(") != 0)
	{
		push_node(postfix, popnode(opstack));
		top_node = opstack->head;
	}
	free(popnode(opstack));
}

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

long long	power(long long base, long long exponent)
{
	long long	result;

	result = 1;
	while (exponent > 0)
	{
		result *= base;
		exponent--;
	}
	return (result);
}

void	push_operand(t_stack *stack, char *operand)
{
	push_node(stack, create_node(ft_strdup(operand)));
}

// Function to pop a token from the stack, free its memory, and convert it to an integer
long long	pop_and_convert_token_to_integer(t_stack *stack)
{
	char		*token;
	long long	value;

	token = popnode(stack)->token;
	value = ft_atoll(token);
	free(token);
	return (value);
}

long long	evaluate_operation(
	long long operand1, long long operand2, char *operator)
{
	if (ft_strcmp(operator, "|") == 0)
		return (operand1 | operand2);
	else if (ft_strcmp(operator, "^") == 0)
		return (operand1 ^ operand2);
	else if (ft_strcmp(operator, "&") == 0)
		return (operand1 & operand2);
	else if (ft_strcmp(operator, "+") == 0)
		return (operand1 + operand2);
	else if (ft_strcmp(operator, "-") == 0)
		return (operand1 - operand2);
	else if (ft_strcmp(operator, "*") == 0)
		return (operand1 * operand2);
	else if (ft_strcmp(operator, "/") == 0)
		return (operand1 / operand2);
	else if (ft_strcmp(operator, "%") == 0)
		return (operand1 % operand2);
	else if (ft_strcmp(operator, "**") == 0)
		return (power(operand1, operand2));
	return (0);
}

void	evaluate_operator(t_stack *stack, char *operator)
{
	long long	operand2;
	long long	operand1;
	long long	result;

	operand2 = pop_and_convert_token_to_integer(stack);
	operand1 = pop_and_convert_token_to_integer(stack);
	result = evaluate_operation(operand1, operand2, operator);
	push_node(stack, create_node(ft_lltoa(result)));
}

long long	evaluate_postfix(t_stack *postfix)
{
	t_stack		stack;
	t_node		*current;
	long long	final_result;

	stack = (t_stack){0};
	current = postfix->tail;
	while (current)
	{
		if (!is_operator(current->token))
			push_operand(&stack, current->token);
		else
			evaluate_operator(&stack, current->token);
		current = current->prev;
	}
	final_result = pop_and_convert_token_to_integer(&stack);
	return (final_result);
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
		push_node(&postfix, popnode(&opstack));
	printf("%lld\n", evaluate_postfix(&postfix));
}

int main(void)
{
	char *postfixExpr[] = { "4", "^", "2", NULL};
	to_postfix(postfixExpr);
}
