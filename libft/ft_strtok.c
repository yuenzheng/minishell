/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:58:45 by ychng             #+#    #+#             */
/*   Updated: 2024/01/23 18:22:21 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*main_str;
	char		*part;
	int			i;

	if (str != NULL)
		main_str = str;
	if (delim == NULL)
		delim = " \t\n\r\v\f\b";
	i = 0;
	while (ft_strchr(delim, main_str[i]) && main_str[i])
		i++;
	if (main_str[i] == '\0')
		return (NULL);
	part = main_str + i;
	while (!ft_strchr(delim, main_str[i]) && main_str[i])
		i++;
	if (main_str[i] != '\0')
	{
		main_str[i] = '\0';
		i++;
	}
	main_str += i;
	return (part);
}
