/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 20:36:38 by ychng             #+#    #+#             */
/*   Updated: 2024/01/23 18:21:24 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	get_total_len(const char *s1, const char *s2, const char *delim)
{
	int	total_len;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	if (delim != NULL)
		total_len += ft_strlen(delim);
	return (total_len);
}

char	*ft_strjoin(const char *s1, const char *s2, const char *delim)
{
	int		total_len;
	char	*new_str;
	int		i;
	int		j;
	int		k;

	if (!s1 || !s2)
		return (NULL);
	total_len = get_total_len(s1, s2, delim);
	new_str = malloc(total_len + 1);
	i = -1;
	while (s1[++i])
		new_str[i] = s1[i];
	j = 0;
	while (delim != NULL && delim[j])
	{
		new_str[i + j] = delim[j];
		j++;
	}
	k = -1;
	while (s2[++k])
		new_str[i + j + k] = s2[k];
	new_str[i + j + k] = '\0';
	return (new_str);
}
