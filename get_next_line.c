/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:28:19 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/08/07 22:51:35 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0]= '\0';
	}
	if (!s2)
		return (NULL);
	newstr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
	free(s1);
	return (newstr);
}

char	*ft_read(int fd, char *s)
{
	char	*ptr;
	int		n;

	ptr = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!ptr)
		return (NULL);
	n = 1;
	while (ft_sreach(s) == 0 && n != 0)
	{
		n = read(fd, ptr, BUFFER_SIZE);
		if (n == -1)
		{
			free(s);
			free(ptr);
			return (0);
		}
		ptr[n] = '\0';
		s = ft_strjoin(s, ptr);
	}
	free(ptr);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*newbuf;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	newbuf = ft_read(fd, newbuf);
	if (newbuf == NULL)
		return (NULL);
	return (newbuf);
}

// int		main(void)
// {
// 	int	fd;

// 	fd = open("main", O_CREAT | O_RDONLY);
// 	printf("%s", get_next_line(fd));
// }