/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:06:29 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/07/18 16:16:53 by ayylaaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strrchr(char *s, int c)
{
	int		len;
	int		i;
	char	*p;

	p = (char *)s;
	len = ft_strlen(s);
	i = 0;
	if (p[len] == (char)c)
		return (&p[len]);
	i = len - 1;
	while (i >= 0)
	{
		if (p[i] == (char)c)
			return (&p[i]);
		i--;
	}
	return (NULL);
}

int	ft_isdigit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] >= 48) || !(s[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}