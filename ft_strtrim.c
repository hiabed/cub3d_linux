/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:45:45 by afadlane          #+#    #+#             */
/*   Updated: 2023/07/15 08:33:05 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	*p;

	p = (char *)s;
	i = 0;
	while (p[i] != (char)c && p[i] != '\0')
		i++;
	if (p[i] == (char)c)
		return (&p[i]);
	return (0);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	size_src;

	i = 0;
	size_src = ft_strlen(src);
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (size_src);
}


char	*ft_strtrim(char *s1, char *set)
{
	int		i;
	int		len;
	char	*p;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	while (i < len - 1 && ft_strchr(set, s1[len -1]))
		len--;
	p = malloc(sizeof(char) * (len - i + 1));
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1 + i, len - i + 1);
	return (p);
}
