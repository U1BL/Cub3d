/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:06:30 by mofaisal          #+#    #+#             */
/*   Updated: 2023/04/08 20:50:42 by mofaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_hold_string(char *saved)
{
	char	*hold;
	int		j;

	j = 0;
	if (!saved)
		return (NULL);
	while (saved[j])
	{
		if (saved[j] == '\n')
		{
			hold = ft_substr(saved, j + 1, ft_strlen(saved));
			free(saved);
			return (hold);
		}
		j++;
	}
	return (NULL);
}

static int	ft_strchr1(char *str, int c)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] && str[i] != c)
			i++;
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

char	*get_line(char *saved)
{
	int	j;

	j = 0;
	if (!saved || saved[0] == '\0')
		return (NULL);
	while (saved[j] != '\0')
	{
		if (saved[j] == '\n')
			return (ft_substr(saved, 0, j + 1));
		j++;
	}
	return (saved);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;
	char		*buffer;
	int			rd;

	rd = 1;
	if (BUFFER_SIZE > INT_MAX || fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (rd > 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
			return (free(saved), free(buffer), (NULL));
		buffer[rd] = '\0';
		saved = ft_strjoin(saved, buffer);
		if (ft_strchr1(saved, '\n') == 0)
			break ;
	}	
	line = get_line(saved);
	saved = get_hold_string(saved);
	return (free(buffer), line);
}
