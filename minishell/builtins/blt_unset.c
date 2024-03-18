/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 06:33:54 by ychng             #+#    #+#             */
/*   Updated: 2024/03/19 04:07:50 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*unset_entry(char *entry, t_subtoken_node *args)
{
	int				env_name_len;
	t_subtoken_node	*current_arg;

	env_name_len = ft_strcspn(entry, "=");
	current_arg = args;
	while (current_arg)
	{
		if (is_special_env_name(*entry))
			return (entry);
		if (env_name_len == ft_strcspn(current_arg->subtoken, "=") \
			&& !ft_strncmp(entry, current_arg->subtoken, env_name_len))
		{
			entry = ft_realloc(entry, ft_strlen(entry) + 1, 1);
			if (!entry)
			{
				printf("ft_realloc failed for entry\n");
				exit(-1);
			}
			*entry = '\0';
			return (entry);
		}
		current_arg = current_arg->next;
	}
	return (entry);
}

int	blt_unset(char **envp, t_subtoken_node *args)
{
	while (*envp)
	{
		*envp = unset_entry(*envp, args);
		envp++;
	}
	return (0);
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