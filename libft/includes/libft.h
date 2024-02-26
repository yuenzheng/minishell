/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 18:00:36 by ychng             #+#    #+#             */
/*   Updated: 2024/02/26 12:25:23 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "sys_headers.h"

// Conversion Functions
int			ft_atoi(const char *str);
long long	ft_atoll(const char *str);
char		*ft_itoa(int n);
char		*ft_lltoa(long long n);

// String Manipulation Functions
int			ft_strlen(const char *str);
int			ft_strspn(const char *str, const char *accept);
int			ft_rstrspn(const char *str, const char *accept);
int			ft_strcspn(const char *str, const char *reject);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, int n);
char		*ft_strchr(const char *str, int c);
char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strncpy(char *dest, const char *src, int n);
char		*ft_strdup(const char *str);
char		*ft_strndup(const char *str, int n);
char		*ft_substr(const char *str, int start, int len);
char		*ft_strjoin(const char *s1, const char *s2, const char *delim);
char		*ft_strtok(char *str, const char *delim);
char		**ft_split(const char *str, const char *delim);

#endif
