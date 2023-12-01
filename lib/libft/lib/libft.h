/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouellet <aouellet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:26:56 by kmehour           #+#    #+#             */
/*   Updated: 2023/11/30 21:05:36 by aouellet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stddef.h>
# include "../../../include/ms.h"


int			ft_isalpha(int c);

int			ft_isdigit(int c);

int			ft_isalnum(int c);

int			ft_isascii(int c);

int			ft_isprint(int c);

int			ft_toupper(int c);

int			ft_tolower(int c);

size_t		ft_strlen(char const *s);

size_t		ft_strlcpy(char *dst, const char *src, size_t size);

size_t		ft_strlcat(char *dest, const char *src, size_t size);

char		*ft_strdup(char const *s);

char		*ft_strchr(const char *s, int c);

int			ft_strcmp(const char *s1, const char *s2);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

char		*ft_strjoin(const char *str1, const char *str2);

char		*ft_strrchr(const char *s, int c);

char		*ft_strnstr(const char *haystack, const char *needle, size_t len);

char		*ft_substr(char const *s, unsigned int start, size_t len);

char		*ft_strtrim(char const *s1, char const *set);

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void		ft_striteri(char *s, void (*f)(unsigned int, char*));

void		*ft_calloc(size_t nmemb, size_t size);

void		ft_bzero(void *s, size_t n);

void		*ft_memcpy(void *dest, const void *src, size_t n);

void		*ft_memset(void *b, int c, size_t len);

void		*ft_memchr(const void *s, int c, size_t n);

void		*ft_memmove(void *dst, const void *src, size_t len);

int			ft_memcmp(const void *s1, const void *s2, size_t n);

void		ft_putstr_fd(char *s, int fd);

void		ft_putchar_fd(char c, int fd);

char		*ft_itoa(int n);

int			ft_atoi(const char *str);

long int	ft_min(long int a, long int b);

char		**ft_split(char const *s, char c);

void		ft_free_tab(char **tab);

char		*get_next_line(int fd);

void	*gc_calloc(size_t nmemb, size_t size);

void	gc_free(void*address);

void	gc_free_all(void);

void gc_detach(void*address);


#endif