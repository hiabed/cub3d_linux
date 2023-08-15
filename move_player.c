/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 10:35:05 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/08/15 21:50:36 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(char **map, t_picture *test)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				test->x_p = x * 64 + 32; // we add 32 to make player in centre
				test->y_p = y * 64 + 32;
				test->color = 0x00FDFD55;
				map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

int ft_check_move(t_picture *data ,double x, double y)
{
    if (data->map_v3[(int)(y / 64)][(int)(data->x_p / 64)] != '1')
    {
        if (data->map_v3[(int)(data->y_p / 64)][(int)(x / 64)] != '1')
        {
            if (data->map_v3[(int)(y / 64)][(int)(x / 64)] != '1')
                return 1;
        }
    }
    return (0);
}

void	move_up(t_picture *data)
{
    double x,y;
    data->ray_pos = data->deta * M_PI / 180;
    x = data->x_p + cos(data->ray_pos) * data->speed;
    y = data->y_p - sin(data->ray_pos) * data->speed;
	if (!data->m_up)
		return ;
    if (!ft_check_move(data, x, y))
        return ;
    else if (!is_wall(data, x / 64, y / 64))
    {
        data->x_p += cos(data->ray_pos) * data->speed;
        data->y_p -= sin(data->ray_pos) * data->speed;
    }
}

void	move_down(t_picture *data)
{
    double x = data->x_p,y = data->y_p;
    data->ray_pos = (data->deta) * M_PI / 180;
    x -= cos(data->ray_pos) * data->speed;
    y += sin(data->ray_pos) * data->speed;
	if (!data->m_down)
		return ;
    if (!ft_check_move(data, x,y))
        return ;
    else if (!is_wall(data, x / 64, y / 64))
    {
        data->x_p -= cos(data->ray_pos) * data->speed;
        data->y_p += sin(data->ray_pos) * data->speed;
    }
}

void	move_right(t_picture *data)
{
    double x, y;
    data->ray_pos = (data->deta + 90) * M_PI / 180;
    x = data->x_p + cos(data->ray_pos) * data->speed;
    y = data->y_p - sin(data->ray_pos) * data->speed;
	if (!data->m_right)
		return ;
    if (!ft_check_move(data, x,y))
        return ;
    else if (!is_wall(data, x / 64, y / 64))
    {
        // change player position after wall check;
        data->x_p += cos(data->ray_pos) * data->speed;
        data->y_p -= sin(data->ray_pos) * data->speed;
    }
}

void	move_left(t_picture *data)
{
    double x, y;
    data->ray_pos = (data->deta - 90) * M_PI / 180;
    x = data->x_p + cos(data->ray_pos) * data->speed;
    y = data->y_p - sin(data->ray_pos) * data->speed;
	if (!data->m_left)
		return ;
     if (!ft_check_move(data, x,y))
        return ;
    else if (!is_wall(data, x / 64, y / 64))
    {
        data->x_p += cos(data->ray_pos) * data->speed;
        data->y_p -= sin(data->ray_pos) * data->speed;
    }
}

void	rotation(t_picture *data)
{
    if(data->deta >= 360)
        data->deta = 0;
	if (data->r_left)
	{
		data->deta += 0.5;
	}
	else if (data->r_right)
	{
		data->deta -= 0.5;
	}
}
