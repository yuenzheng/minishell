/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:11:35 by ychng             #+#    #+#             */
/*   Updated: 2024/03/03 01:41:12 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memcpy(void *dest, const char *src, size_t n)
{
	char	*destination;
	char	*source;

	if (!dest || !src)
		return (dest);
	destination = (char *)dest;
	source = (char *)src;
	while (n--)
		*destination++ = *source++;
	return (dest);
}
