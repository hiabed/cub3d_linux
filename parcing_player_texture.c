/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_player_texture.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:44:57 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/08/07 22:53:53 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     check_map_extantion(char *map)
{
    int i;

    i = 0;
    while (map[i])
        i++;
    while (i >= 0)
    {
        if (map[i] == '.' && map[i])
        {
            if (map[i + 1] == 'c' && map[i + 2] == 'u' && map[i + 3] == 'b' && !map[i + 4])
                return (0);
        }
        i--;
    }
    return (1);
}

int     check_double_element(char **map)
{
    int     i;
    int     count;
    int     count1;
    int     count2;
    int     count3;
    int     count4;
    char    **a;
    char    *trim;

    i = 0;
    count = 0;
    count1 = 0;
    count2 = 0;
    count3 = 0;
    count4 = 0;
    while (map[i])
    {
        trim = ft_strtrim(map[i], " ");
        if (trim[0] != 1)
        {
            a = ft_split(map[i], ' ');
            if (!ft_strcmp(a[0], "NO"))
                count++;
            else if (!ft_strcmp(a[0], "SO"))
                count1++;
            else if (!ft_strcmp(a[0], "EA"))
                count2++;
            else if (!ft_strcmp(a[0], "WE"))
                count3++;
            else if (!ft_strcmp(a[0], "F") || !ft_strcmp(a[0], "C"))
                count4++;
        }
        i++;
    }
    if (count + count1 + count2 + count3 == 4 && count4 == 2)
        return (0);
    return (1);
}

int     check_wall_text(char **src)
{
    int i;
    int j;
    int count;
    int count1;
    int count2;
    int count3;
    char    *trim;

    count1 = 0;
    count2 = 0;
    count3 = 0;
    count = 0;
    i = 0;
    j = 0;
    while (src[i])
    {
        trim = ft_strtrim(src[i], " ");
        if (trim[0] == 'N' && trim[1] == 'O')
            count++;
        else if (trim[0] == 'W' && trim[1] == 'E')
            count1++;
        else if (trim[0] == 'E' && trim[1] == 'A')
            count2++;
        else if (trim[0] == 'S' && trim[1] == 'O')
            count3++;
        i++;
    }
    if (count + count1 + count2 + count3 == 4)
        return (0);
    return (1);
}