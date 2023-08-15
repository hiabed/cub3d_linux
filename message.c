# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
//# include "cub3d.h"

int	ft_exit(void)
{
	write(1,"YOU ARE EXIT FROM CUB\n",22);
	exit(1);
}

typedef struct s_img
{
	char	dir;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		heigth;
	char	*addr;
	void	*ptr;
	struct s_img *next;
} t_img;

typedef struct
{
	int speed;
	float x;
	float y;
	float teta;
	int m_r;
	int m_l;
	int m_u;
	int m_d;
	int rot_rhit;
	int rot_left;
	void *mlx;
	void *win;
	t_img *img;
	t_img *img1;
	char **map;
}	t_test;

void	my_mlx_pixel_put1(t_img *data, int x, int y, int color)
{
	char	*dst;
	if (x < 0 || x >= 640 || y < 0 || y >= 640)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_put(t_test *test, int x, int y, int color)
{
	char	*dst;
	if (x < 0)
		test->x = 630;
	if (y < 0)
		test->y = 630;
	if (x > 640)
		test->x = 10;
	if (y > 640)
		test->y = 10;
	if (x < 0 || x >= 640 || y < 0 || y >= 640)
		return ;
	dst = test->img->addr + (y * test->img->line_length + x * (test->img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	put_square(t_test * test, int x, int y, int color)
{
	int old_x = x,old_y = y;
	while (x < old_x + 64)
	{
		y = old_y;
		while (y < old_y + 64)
			my_mlx_pixel_put1(test->img, x, y++, color);
		x++;
	}
}

void	put_player(t_test *test, int color)
{
	float teta = 0;
	float x,y;
	float t_rad;
	while (teta < 360)
	{
		x = test->x, y = test->y;
		t_rad = M_PI * teta / 180;
		while (sqrt(pow(x - test->x, 2) + pow(y - test->y, 2)) < 10)
		{
			my_mlx_put(test, x, y, color);
			x += cos(t_rad);
			y -= sin(t_rad);
		}
		teta++;
	}
	x = test->x, y = test->y;
	t_rad = M_PI * test->teta / 180;
	for (int i = 0; i < 20 ; i++)
	{
		my_mlx_put(test,x,y,color);
		x += cos(t_rad);
		y -= sin(t_rad);
	}
 }

// void	put_player(t_test *test, int color)
// {
// 	float	rad;
// 	float	x;
// 	float	y;
// 	float	teta;

// 	teta = 0;
// 	while (teta < 360)
// 	{
// 		x = test->x;
// 		y = test->y;
//  		rad = M_PI * teta / 180;
// 		while (sqrt(pow(x - test->x, 2) + pow(y - test->y, 2)) < 5)
// 		{
// 			my_mlx_put(test, x, y, color);
// 			x += cos(rad);
// 			y -= sin(rad);
// 		}
// 		teta++;
// 	}
// 	int	i;

// 	i = 0;
// 	x = test->x;
// 	y = test->y;
// 	while (i++ < 10)
// 	{
// 		my_mlx_put(test, x, y, color);
// 		x += cos(rad);
// 		y -= sin(rad);
// 	}
// }

void init_var(t_test * test)
{
	test->x = 320;
	test->y = 320;
	test->m_r = 0;
	test->m_l = 0;
	test->m_u = 0;
	test->m_d = 0;
	test->rot_rhit = 0;
	test->rot_left = 0;
	test->teta = 90;
	test->speed = 3;
	test->map = malloc(11*sizeof(char*));
	test->map[0] = "1111111111";
	test->map[1] = "1000000001";
	test->map[2] = "1000000001";
	test->map[3] = "1000000001";
	test->map[4] = "1000100001";
	test->map[5] = "1000200001";
	test->map[6] = "1000100001";
	test->map[7] = "1000000001";
	test->map[8] = "1000000001";
	test->map[9] = "1111111111";
	test->map[10] = NULL;
}

void f1(t_test *test)
{
	int x,y = 0;
	while (test->map[y])
	{
		x = 0;
		while (test->map[y][x]){
			if (test->map[y][x] == '1')
				put_square(test, x * 64, y * 64, 0x000000CD);
			if (test->map[y][x] == '0')
				put_square(test, x * 64, y * 64, 0x00FDFD96);
			if (test->map[y][x] == '2')
				put_square(test, x * 64, y * 64, 0x00FDFD55);
			x++;
		}
		y++;
	}
	put_player(test, 16711680);
	mlx_put_image_to_window(test->mlx, test->win, test->img->ptr, 0, 0);
}

void mov_up(t_test *test)
{
	if (test->m_u == 0)
		return ;
	float t_rad;
	t_rad = M_PI * test->teta / 180;
	test->x += cos(t_rad) * test->speed;
	test->y -= sin(t_rad) * test->speed;
}

void mov_left(t_test *test)
{
	if (test->m_l == 0)
		return ;
	float t_rad;
	t_rad = M_PI * (test->teta + 90) / 180;
	test->x += cos(t_rad) * test->speed;
	test->y -= sin(t_rad) * test->speed;
}

void mov_rhit(t_test *test)
{
	if (test->m_r == 0)
		return ;
	float t_rad;
	t_rad = M_PI * (test->teta - 90) / 180;
	test->x += cos(t_rad) * test->speed;
	test->y -= sin(t_rad) * test->speed;
}

void mov_down(t_test *test)
{
	if (test->m_d == 0)
		return ;
	float t_rad;
	t_rad = M_PI * test->teta / 180;
	test->x -= cos(t_rad) * test->speed;
	test->y += sin(t_rad) * test->speed;
}

int rotation(t_test *test)
{
	if (test->rot_left == 1)
		test->teta += 1;
	if (test->rot_rhit == 1)
		test->teta -= 1;
	return 0;
}

int motion(t_test *test)
{
	mov_rhit(test);
	mov_left(test);
	mov_up(test);
	mov_down(test);
	rotation(test);
	f1(test);
	return (0);
}

int	relesse_key(int key, t_test *test)
{
	if (key == 85)//3
		test->rot_rhit = 0;
	if (key == 83)//1
		test->rot_left = 0;
	if (key == 126)
		test->m_u = 0;
	if (key == 125)
		test->m_d = 0;
	if (key == 124)
		test->m_r = 0;
	if (key == 123)
		test->m_l = 0;
	return (0);
}

int	presse_key(int key, t_test *test)
{
	if (key == 85)//3
		test->rot_rhit = 1;
	if (key == 83)//1
		test->rot_left = 1;
	if (key == 126)
		test->m_u = 1;
	if (key == 125)
		test->m_d = 1;
	if (key == 124)
		test->m_r = 1;
	if (key == 123)
		test->m_l = 1;
	if (key == 53)
		ft_exit();
	return (0);
}

int main(int ac, char **av)
{
	t_test *test;

	test = malloc(sizeof(t_test));
	test->img = malloc(sizeof(t_img));
	test->mlx = mlx_init();
	test->win = mlx_new_window(test->mlx, 640, 640, "TEST");
	test->img->ptr = mlx_new_image(test->mlx, 640, 640);
	test->img->addr = mlx_get_data_addr(test->img->ptr, &test->img->bits_per_pixel,
	 	&test->img->line_length, &test->img->endian);
	init_var(test);
	f1(test);
	put_player(test, 16711680);
	mlx_hook(test->win, 17, 0, ft_exit, NULL);
	mlx_hook(test->win, 2, 0,presse_key, test);
	mlx_hook(test->win, 3, 0,relesse_key, test);
	mlx_loop_hook(test->mlx, motion, test);
	mlx_loop(test->mlx);
}