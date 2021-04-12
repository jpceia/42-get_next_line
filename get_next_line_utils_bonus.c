/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:48:24 by jceia             #+#    #+#             */
/*   Updated: 2021/04/12 17:50:03 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

char	*ft_strcat(char *dest, const char *src)
{
	int		n;
	int		index;

	n = ft_strlen(dest);
	index = 0;
	while (src[index])
	{
		dest[n + index] = src[index];
		index++;
	}
	dest[n + index] = 0;
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*res;

	size = ft_strlen(s1);
	size += ft_strlen(s2);
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	ft_strcat(res, s1);
	ft_strcat(res, s2);
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	index;
	size_t	s_len;
	char	*res;

	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (start + len > s_len)
		len = s_len - start;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	index = 0;
	while (s[start + index] && index < len)
	{
		res[index] = s[start + index];
		index++;
	}
	res[index] = '\0';
	return (res);
}

char	*freeable_empty_string(void)
{
	char	*e;

	e = malloc(1);
	if (!e)
		return (NULL);
	*e = '\0';
	return (e);
}
