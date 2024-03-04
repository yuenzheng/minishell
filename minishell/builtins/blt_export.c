/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:10:05 by ychng             #+#    #+#             */
/*   Updated: 2024/03/05 03:40:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_envp_size(char **envp)
{
	int	envp_size;

	envp_size = 0;
	while (envp[envp_size])
		envp_size++;
	return (envp_size);
}

void	copy_envp_contents(char **envp, char **envp_copy)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (!envp_copy[i])
		{
			printf("malloc failed for envp_copy[i]\n");
			exit(-1);
		}
	}
	envp_copy[i] = NULL;
}

char	**copy_envp(char **envp)
{
	int		envp_size;
	char	**envp_copy;

	envp_size = count_envp_size(envp);
	envp_copy = malloc(sizeof(char *) * (envp_size + 1));
	if (!envp_copy)
	{
		printf("malloc failed for new_envp\n");
		exit(-1);
	}
	copy_envp_contents(envp, envp_copy);
	return (envp_copy);
}

bool	validate_env_name(char *subtoken)
{
	if (is_special_env_name(*subtoken))
		return (false);
	while (*subtoken && is_valid_env_name(*subtoken))
		subtoken++;
	return (*subtoken == '\0');
}

int	count_params_size(t_subtoken_node *params, char **envp)
{
	int	export_envp_size;

	export_envp_size = 0;
	while (params)
	{
		if (!validate_env_name(params->subtoken))
			break ;
		if (getenv(params->subtoken) == NULL)
			export_envp_size++;
		params = params->next;
	}
	return (export_envp_size);
}

void	copy_envp_to_export_envp(char **envp, char **export_envp)
{
	while (*envp)
		*export_envp++ = ft_strdup(*envp++);
}

void	copy_params_to_export_envp(t_subtoken_node *params, char **export_envp, int i)
{
	while (params)
	{
		if (!validate_env_name(params->subtoken))
			return ;	
		export_envp[i++] = ft_strdup(params->subtoken);
		params = params->next;	
	}
}

int	get_max_len(char **export_envp)
{
	int	max_len;
	int	len;

	max_len = 0;
	while (*export_envp)
	{
		len = ft_strlen(*export_envp);
		if (max_len < len)
			max_len = len;
		export_envp++;
	}
	return (max_len);
}

void	pad_entries(char **export_envp, int max_len)
{
	int		len;
	int		pad_len;
	char	*padded_entry;

	while (*export_envp)
	{
		len = ft_strlen(*export_envp);
		if (len < max_len)
		{
			pad_len = max_len - len;
			padded_entry = ft_realloc(*export_envp, len + 1, max_len + 1);
			if (!padded_entry)
			{
				printf("ft_realloc failed for padded_entry\n");
				exit(-1);
			}
			ft_memset(padded_entry + len, ' ', pad_len);
			padded_entry[len + pad_len] = '\0';
			*export_envp = padded_entry;
		}
		export_envp++;
	}
}

void	pad_export_envp(char **export_envp)
{
	int	max_len;

	max_len = get_max_len(export_envp);
	pad_entries(export_envp, max_len);
}

int	blt_export(t_subtoken_node *params, char **envp)
{
	int		envp_size;
	int		params_size;
	char	**export_envp;

	envp_size = count_envp_size(envp);
	params_size = count_params_size(params, envp);
	export_envp = malloc(sizeof(char *) * (envp_size + params_size + 1));
	if (!export_envp)
	{
		printf("malloc failed for export_envp\n");
		exit(-1);
	}
	copy_envp_to_export_envp(envp, export_envp);
	copy_params_to_export_envp(params, export_envp, envp_size);
	export_envp[envp_size + params_size] = NULL;
	pad_export_envp(export_envp);
	while(*export_envp)
	{
		printf("%s\n", *export_envp);
		free(*export_envp);
		export_envp++;
	}
}

int	main(int argc, char **argv, char **envp)
{
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
