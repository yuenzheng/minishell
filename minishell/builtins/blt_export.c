/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:10:05 by ychng             #+#    #+#             */
/*   Updated: 2024/03/06 23:29:01 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**create_export_envp(char **envp, t_subtoken_list *params_list)
{
	int		envp_size;
	int		params_size;
	char	**export_envp;

	envp_size = count_envp_size(envp);
	params_size = count_params_size(params_list);
	export_envp = malloc(sizeof(char *) * (envp_size + params_size + 1));
	if (!export_envp)
	{
		printf("malloc failed for export_envp\n");
		exit(-1);
	}
	return (export_envp);
}

static void	copy_to_export_envp(char **export_envp, char **envp, \
				t_subtoken_list *params_list)
{
	from_envp(export_envp, envp);
	from_params(export_envp + count_envp_size(envp), params_list);
}

static void	pad_export_envp(char **export_envp)
{
	int	max_len;

	max_len = get_max_name_len(export_envp);
	while (*export_envp)
	{
		*export_envp = pad_name(*export_envp, max_len);
		export_envp++;
	}
}

static void	print_export_envp(char **export_envp)
{
	char	*entry_copy;
	char	*name;
	char	*value;

	while (*export_envp)
	{
		if (is_underscore(**export_envp) && *(*export_envp + 1) == ' ')
		{
			export_envp++;
			continue ;
		}
		entry_copy = ft_strdup(*export_envp);
		name = ft_strtrim(ft_strtok(entry_copy, "="), " ");
		value = ft_strchr(*export_envp, '=');
		if (value)
		{
			value++;
			printf("declare -x %s=\"%s\"\n", name, value);
		}
		else
			printf("declare -x %s\n", name);
		free(entry_copy);
		free(name);
		export_envp++;
	}
}

int	blt_export(char **envp, t_subtoken_node *params)
{
	t_subtoken_list	*params_list;
	char			**export_envp;

	params_list = malloc(sizeof(t_subtoken_list));
	params_list->head = 0;
	params_list->tail = 0;
	link_subtoken_node(params, params_list);
	export_envp = create_export_envp(envp, params_list);
	copy_to_export_envp(export_envp, envp, params_list);
	pad_export_envp(export_envp);
	radix_sort(export_envp);
	print_export_envp(export_envp);
	while(*export_envp)
	{
		// printf("%s\n", *export_envp);
		free(*export_envp);
		export_envp++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_subtoken_node	fir;
	t_subtoken_node	sec;
	t_subtoken_node	thi;

	fir.next = &sec;
	sec.next = &thi;
	thi.next = NULL;

	fir.subtoken = "Ahithere=";
	sec.subtoken = "ya12";
	thi.subtoken = "_7";
	blt_export(envp, &fir);
}
