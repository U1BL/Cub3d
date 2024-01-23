/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:03:42 by mofaisal          #+#    #+#             */
/*   Updated: 2023/04/08 20:51:12 by mofaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 13
# endif

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include ".././libft/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strjoin(char *left_str, char *buff);

size_t	ft_strlen(char const *s);

void	*ft_calloc(size_t count, size_t size);

void	ft_bzero(void *s, size_t n);

char	*get_next_line(int fd);

#endif