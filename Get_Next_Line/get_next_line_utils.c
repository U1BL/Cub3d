/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 14:29:54 by ahassan           #+#    #+#             */
/*   Updated: 2023/04/18 17:15:46 by mofaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *saved, char *buffer)
{
	int		i;
	int		j;
	char	*joined;

	i = 0;
	j = 0;
	if (!saved)
	{
		saved = (char *)ft_calloc(sizeof(char), 1);
		saved[0] = '\0';
	}
	if (!buffer)
		return (NULL);
	joined = (char *)malloc((ft_strlen(saved) + ft_strlen(buffer) + 1));
	if (!joined)
		return (free(saved), free(joined), NULL);
	while (saved[i])
		joined[j++] = saved[i++];
	i = 0;
	while (buffer[i])
		joined[j++] = buffer[i++];
	joined[j] = '\0';
	if (joined[0] == '\0')
		return (free(saved), free(joined), NULL);
	return (free(saved), joined);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	slen;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	slen = ft_strlen(s);
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (start < slen && len > i)
		substr[i++] = s[start++];
	substr[i] = '\0';
	if (!substr[0])
	{
		free(substr);
		return (NULL);
	}
	return (substr);
}
