/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:10:05 by ychng             #+#    #+#             */
/*   Updated: 2024/03/06 04:05:12 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**create_export_envp(t_subtoken_node *params, char **envp)
{
	int		envp_size;
	int		params_size;
	char	**export_envp;

	envp_size = count_envp_size(envp);
	params_size = count_params_size(params);
	export_envp = malloc(sizeof(char *) * (envp_size + params_size + 1));
	if (!export_envp)
	{
		printf("malloc failed for export_envp\n");
		exit(-1);
	}
	return (export_envp);
}

static void	copy_envp_to_export_envp(char **envp, char **export_envp)
{
	while (*envp)
		*export_envp++ = ft_strdup(*envp++);
	*export_envp = NULL;
}

static void	copy_params_to_export_envp(t_subtoken_node *params, \
				char **export_envp)
{
	export_envp += count_envp_size(export_envp);
	while (params)
	{
		if (!validate_env_name(params->subtoken))
			return ;
		*export_envp++ = ft_strdup(params->subtoken);
		params = params->next;
	}
	*export_envp = NULL;
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

int	blt_export(t_subtoken_node *params, char **envp)
{
	char	**export_envp;

	export_envp = create_export_envp(params, envp);
	copy_envp_to_export_envp(envp, export_envp);
	copy_params_to_export_envp(params, export_envp);
	pad_export_envp(export_envp);
	while(*export_envp)
	{
		printf("%s\n", *export_envp);
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

	fir.subtoken = "hithere";
	sec.subtoken = "ya12";
	thi.subtoken = "_7";
	blt_export(&fir, envp);
}
