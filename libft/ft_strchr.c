/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mofaisal <mofaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:58:48 by mofaisal          #+#    #+#             */
/*   Updated: 2023/04/17 17:44:24 by mofaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	slen;

	slen = 0;
	while (s[slen] != 0)
		slen++;
	if (c == 0)
		return ((char *)s + slen);
	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

int	ft_wallcheck(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] && !(str[i] >= 50 && str[i] <= 126))
			i++;
		if (str[i] == (str[i] >= 50 && str[i] <= 126))
			return (0);
	}
	return (1);
}
