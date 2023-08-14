/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:50:00 by ayylaaba          #+#    #+#             */
/*   Updated: 2023/08/13 20:55:59 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_perror(void)
{
	write(2, "ERROR\n", 6);
	exit(1);
}

int	ft_exit(void)
{
	write(1, "safi barka elik \n", 17);
	exit(0);
}

char	*get_content(char *str, char c)
{
	int		i;
	int		i2;
	char	*content;

	i = 0;
	i2 = 0;
	while (str[i] && str[i] != c) // skip object (C or F)
		i++;
	while (str[i] == '\t' || str[i] == ' ') // skip space
	{
		i++;
		i2++;
	}
	content = malloc(sizeof(char) * (ft_strlen(str + i) + 1));
	if (!content)
		return (NULL);
	i2 = 0;
	while (str[i])
		content[i2++] = str[i++];
	content[i2] = '\0';
	return (content);
}

int	check_text_ext(char **map)
{
	int		i;
	char	*trim;
	char	*ext;
	char	**wall_pos;
	char	*line_content;

	i = 0;
	while (map[i])
	{
		trim = ft_strtrim(map[i], " ");
		wall_pos = ft_split(trim, ' ');
		if (!ft_strcmp(wall_pos[0], "NO") || !ft_strcmp(wall_pos[0], "WE")
			|| !ft_strcmp(wall_pos[0], "SO") || !ft_strcmp(wall_pos[0], "EA"))
		{
			line_content = get_content(trim, ' ');
			if (!line_content || !line_content[0])
				return (1);
			ext = ft_strrchr(line_content, '.');
			ext++;
			if (ft_strcmp(ext, "xpm"))
				return (1);
		}
		i++;
	}
	return (0);
}

void	my_put_pixl(t_picture *test, int x, int y, int color)
{
	char	*hold_pic_addr;

	if (x < 0 || x >= 640 || y < 0 || y >= 640)
		return ;
	hold_pic_addr = test->adrr + (y * test->len + x * (test->bit_pixl / 8));
	*(unsigned int *)hold_pic_addr = color;
}

void	draw_squar(t_picture *test, int old_x, int old_y, int color)
{
	int	x;
	int	y;

	x = old_x;
	while (x <= old_x + 62)
	{
		y = old_y;
		while (y <= old_y + 62)
			my_put_pixl(test, x, y++, color);
		x++;
	}
}

int	is_wall(t_picture *data, float x, float y)
{
	int	j;
	int	i;

	j = 0;
	while (data->map_v3 && data->map_v3[j])
		j++;
	if (y >= j || x < 0 || y < 0)
		return (1);
	i = 0;
	while (data->map_v3[(int)y] && data->map_v3[(int)y][(int)i])
		i++;
	if (x >= i - 1)
		return 1;
	int k = 0;
	if (data->map_v3[(int)y][(int)x] == '1')
	{
		return (1);
	}
	return (0);
}

void	draw_horizontal_ray(t_picture *data, float angle)
{
	int		i;
	float	x;
	float	y;
	float	rad;

	rad = angle * M_PI / 180;
	x = data->x_p;
	y = data->y_p;
	i = 0;
	while (i <= data->ray_distance_hor)
	{
		my_put_pixl(data, x, y, data->color);
		x += cos(rad);
		y -= sin(rad);
		i++;
	}
}

void	draw_vertical_ray(t_picture *data, float angle)
{
	int		i;
	float	x;
	float	y;
	float	rad;
	
	x = data->x_p;
	y = data->y_p;
	rad = angle * M_PI / 180;
	i = 0;
	while (i <= data->ray_distance_ver)
	{
		my_put_pixl(data, x, y, data->color);
		x += cos(rad);
		y -= sin(rad);
		i++;
	}
}

//  struct	s_data {
// 	void	*tex;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// 	int w;
// 	int h;
// }	;


// unsigned int    ft_get_color(t_picture * data, int j, struct s_data * tex)
// {
//     int                offset_x;
//     int                offset_y;
//     unsigned int    color;
//     char            *dst;

// 	if (data->ray_distance_hor < data->ray_distance_ver)
//     	offset_x = ((int )(data->tx_hor + data->ty_hor) % 64) * tex->w / 64;
// 	else
//     	offset_x = ((int )(data->tx_ver + data->ty_ver) % 64) * tex->w / 64;

//     offset_y = (j - ((640 / 2) - (data->wall_tall / 2))) * \
//                     ((float)tex->h / 640);
			
//     color = 0;
//     if (offset_x < tex->w && offset_y < tex->h && offset_x >= 0 \
//                                             && offset_y >= 0)
//     {
//         dst = tex->addr + (offset_y * tex->line_length + offset_x \
//                                         * (tex->bits_per_pixel / 8));
//         color = *(unsigned int *)dst;
//     }
//     return (color);
// }

void	draw_wall(t_picture * data, int color)
{
	// struct	s_data tex;
	double		start;
	double		end;

	// tex.tex = mlx_xpm_file_to_image(data->ptr, "message.xpm", &tex.w, &tex.h);
	// tex.addr = mlx_get_data_addr(tex.tex, &tex.bits_per_pixel, &tex.line_length, &tex.endian);
	start = 320 - (data->wall_tall / 2);
	end = start + data->wall_tall;

	for (int i = 0; i < start; i++) {
		my_put_pixl(data, data->f , i , 11796550);
	}

	while (start < end)
	{
		my_put_pixl(data, data->f , start , color);
		start++;
	}

	for (int i = end; i < 640; i++) {
		my_put_pixl(data, data->f , i , 7882390);
	}
}

void	draw_walls(t_picture * data)
{
	int	s;

	s = (data->ray_distance_hor > data->ray_distance_ver);
	if (data->ray_distance_hor == data->ray_distance_ver)
		s = data->old_s;
	data->old_s = s;
	if (data->dir_v == 'E' && s)
		draw_wall(data, 0x033ff1);
	if (data->dir_v == 'W' && s)
		draw_wall(data, 0xa4b110);
	if (data->dir_h == 'N' && !s)
		draw_wall(data, 0xf54fff);
	if (data->dir_h == 'S' && !s)
		draw_wall(data, 0xf99f3f);
}

void	put_player(t_picture *test, int color)
{
	double	rad;
	double	x;
	double	y;
	double	angle;
	double	cur_angl;

	angle = 0;
	//draw player;
	while (angle < 360)
	{
		rad = angle * M_PI / 180;
		x = test->x_p;
		y = test->y_p;
		while ((sqrt(pow(test->x_p - x, 2) + pow(test->y_p - y, 2)) < 5))
		{
			//my_put_pixl(test, x, y, color);
			x += cos(rad);
			y -= sin(rad);
		}
		angle++;
	}
	//casting rays;
	test->color = 0x0ff0000; //red;
	angle = test->deta + 30;
	int i = 0;
	test->f = 0;
	while (test->f < 640)
	{
			hor_int(test, angle, x, y); // just to get distance horizontal
			ver_int(test, angle, x, y); // just to get distance vertical
			if (test->ray_distance_hor <= test->ray_distance_ver)
				i = 1;
			else if (test->ray_distance_ver <= test->ray_distance_hor)
				i = 0;
			cur_angl = (test->deta - angle);
			if (!i)
				test->new_ray_distance = test->ray_distance_ver * cos(((cur_angl) * M_PI / 180));
			else 
				test->new_ray_distance = test->ray_distance_hor * cos(((cur_angl) * M_PI / 180));
			test->dist_p_screen	= 320 / tan(30 * M_PI / 180);
			test->wall_tall	= ((64 / test->new_ray_distance) * test->dist_p_screen);
			if(test->wall_tall >= 640) //remove the lag when the wall is bigger than the size of the screen;
				test->wall_tall = 640;
			draw_walls(test);
			test->f++;
			angle -= 64.0 / 640.0;
	}
}

void	draw_map(char **map, t_picture *test)
{
	// int	x;
	// int	y;
	

	// y = 0;
	// while (map[y])
	// {
	// 	x = 0;
	// 	while (map[y][x])
	// 	{
	// 		if (map[y][x] == '1')
	// 			draw_squar(test, x * 64, y * 64, 0x000000CD);
	// 		if (map[y][x] == '0')
	// 			draw_squar(test, x * 64, y * 64, 30778801);
	// 		x++;
	// 	}
	// 	y++;
	// }
	test->image_adrr = mlx_new_image(test->ptr, 640, 640);
	test->adrr = mlx_get_data_addr(test->image_adrr, &test->bit_pixl,
	 		&test->len, &test->end);
	put_player(test, 0x00FDFD55);
	//printf ("------> x == %d, y == %d, color == %d\n", test->data->x,
	//test->data->y, test->data->color);
	mlx_put_image_to_window(test->ptr, test->wind, test->image_adrr, 0, 0);
}

int	give_key(int key, t_picture *test)
{
	printf("key: %d\n", key);
	if (key == 65361)
		test->r_left = 1;
	if (key == 65363)
		test->r_right = 1;
	if (key == 119) //w
		test->m_up = 1;
	if (key == 115) //s
		test->m_down = 1;
	if (key == 100) //d
		test->m_left = 1;
	if (key == 97)
		test->m_right = 1;
	if (key == 65307) //esc
	{
		write(1, "thella ;)\n", 10);
		free(test);
		exit(0);
	}
	return (0);
}

int	animate_moves(t_picture *test)
{
	test->speed = 0.5;
	rotation(test);
	move_up(test);
	move_down(test);
	move_left(test);
	move_right(test);
	draw_map(test->map_v3, test);
	return (0);
}

int	key_released(int key, t_picture *test)
{
	if (key == 65361)
		test->r_left = 0;
	else if (key == 65363)
		test->r_right = 0;
	else if (key == 119)
		test->m_up = 0;
	else if (key == 115)
		test->m_down = 0;
	else if (key == 100)
		test->m_left = 0;
	else if (key == 97)
		test->m_right = 0;
	return (0);
}

void	initialize_the_angle_of_player(t_picture *test)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (test->map_v3[j])
	{
		i = 0;
		while (test->map_v3[j][i])
		{
			if (test->map_v3[j][i] == 'N')
			{
				test->deta = 90;
			}
			else if (test->map_v3[j][i] == 'S')
				test->deta = 270;
			else if (test->map_v3[j][i] == 'E')
				test->deta = 0;
			else if (test->map_v3[j][i] == 'W')
				test->deta = 180;
			i++;
		}
		j++;
	}
}

t_picture	*initialize_structure(int ac, char **av)
{
	t_picture	*test;
	int			fd;
	char		*map_content;

	test = malloc(sizeof(t_picture));
	if (ac != 2)
		ft_perror();
	if (!test)
	{
		printf("Error\n");
		return (NULL);
	}
	test->move_check = 0;
	test->m_up = 0;
	test->m_down = 0;
	test->m_left = 0;
	test->m_right = 0;
	test->r_left = 0;
	test->r_right = 0;
	fd = open(av[1], O_RDONLY);
	map_content = get_next_line(fd);
	test->map_v2 = ft_split(map_content, '\n');
	test->map_v3 = test->map_v2 + 6;
	initialize_the_angle_of_player(test);
	return (test);
}

int	main(int ac, char **av)
{
	t_picture	*test;

	test = initialize_structure(ac, av);
	if (check_map_extantion(av[1]) || check_character(test->map_v2)
		|| check_wall_text(test->map_v2) || check_double_element(test->map_v2))
		ft_perror();
	init_player(test->map_v3, test);
	test->ptr = mlx_init();
	test->wind = mlx_new_window(test->ptr, 640, 640, "cub3d");
	test->image_adrr = mlx_new_image(test->ptr, 640, 640);
	test->adrr = mlx_get_data_addr(test->image_adrr, &test->bit_pixl,
			&test->len, &test->end);
	test->r_left = 0;
	test->r_right = 0;
	draw_map(test->map_v3, test);
	mlx_hook(test->wind, 17, 0, ft_exit, NULL);
	mlx_hook(test->wind, 2, 3, give_key, test);
	mlx_hook(test->wind, 3, 0, key_released, test);
	mlx_loop_hook(test->ptr, animate_moves, test);
	mlx_loop(test->ptr);
}



