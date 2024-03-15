/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 06:33:54 by ychng             #+#    #+#             */
/*   Updated: 2024/03/15 16:43:40 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	is_match(char *str, t_subtoken_node *params)
{
	int	name_len;

	name_len = ft_strcspn(str, "=");
	while (params)
	{
		if (ft_strncmp(str, params->subtoken, name_len) == 0)
			return (true);
		params = params->next;
	}
	return (false);
}

static void	unset_environment_variables(char **envp, t_subtoken_node *params)
{
	while (*envp)
	{
		if (is_match(*envp, params))
		{
			*envp = ft_realloc(*envp, ft_strlen(*envp) + 1, 1);
			**envp = '\0';
		}
		envp++;
	}
}

static void	unset_params_list(t_subtoken_list *params_list, \
				t_subtoken_node *params)
{
	t_subtoken_node	*current;
	int				len;

	current = params_list->head;
	while (current)
	{
		if (is_match(current->subtoken, params))
		{
			len = ft_strlen(current->subtoken);
			current->subtoken = ft_realloc(current->subtoken, len + 1, 1);
			*current->subtoken = '\0';
		}
		current = current->next;
	}
}

void	blt_unset(char **envp, t_subtoken_node *params, \
				t_subtoken_list *params_list)
{
	unset_environment_variables(envp, params);
	if (params_list != NULL)
		unset_params_list(params_list, params);
	exit(0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	**temp;

// 	temp = envp;
// 	envp = malloc(sizeof(char *) * (count_envp_size(envp) + 1));
// 	from_envp(envp, temp);

// 	t_subtoken_node	first;
// 	t_subtoken_node	second;
// 	t_subtoken_node	third;
// 	t_subtoken_node	fourth;
// 	t_subtoken_node	fifth;

// 	first.next = &second;
// 	second.next = &third;
// 	third.next = &fourth;
// 	fourth.next = &fifth;;
// 	fifth.next = NULL;

// 	first.subtoken = "XDG_RUNTIME_DIR";
// 	second.subtoken = "bye";
// 	third.subtoken = "LOGNAME";
// 	fourth.subtoken = "COLORTERM=";
// 	fifth.subtoken = "NAME=MAX";

// 	blt_unset(envp, NULL, &first);
// 	int	i;

// 	i = -1;
// 	blt_export(&envp, NULL);
// 	free_envp(envp);
// }