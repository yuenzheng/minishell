/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 18:00:36 by ychng             #+#    #+#             */
/*   Updated: 2024/01/23 18:35:07 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "sys_headers.h"

// Conversion Functions
int			ft_atoi(const char *str);
long long	ft_atoll(const char *str);
char		*ft_itoa(int n);

// String Manipulation Functions
int			ft_strlen(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, int n);
char		*ft_strchr(const char *str, int c);
char		*ft_strdup(const char *str);
char		*ft_strjoin(const char *s1, const char *s2, const char *delim);
char		*ft_strtok(char *str, const char *delim);
char		**ft_split(const char *str, const char *delim);

#endif
