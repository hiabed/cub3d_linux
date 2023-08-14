/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:40:38 by afadlane          #+#    #+#             */
/*   Updated: 2023/08/07 17:10:18 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdup(char *s1)
{
	char	*p;
	int		i;

	if (!s1 || !s1[0])
		return (NULL);
	i = 0;
	p = malloc(ft_strlen(s1) + 1);
	if (!p)
		return (NULL);
	while (s1[i] != '\0' && s1)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
