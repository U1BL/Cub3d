#include "cub3d.h"

int	parse_check(int argc, char *argv[], t_cub *map)
{
	if (argc < 2)
		return (ft_putstr_fd("Few Arguments Entered\n", 2), 0);
	else if (argc > 2)
		return (ft_putstr_fd("Error: Too Many Arguments Entered\n", 2), 0);
	if (!check_file(argv[1]) || !init_map(map, argv[1]))
		return (0);
	map->colors = malloc(sizeof(char*) * 2);
    if (!map->colors)
        return (0);
    map->colors[0] = malloc(ft_strlen(map->ccieling) + 1);
    map->colors[1] = malloc(ft_strlen(map->cfloor) + 1);
    if (!map->colors[0] || !map->colors[1]) {
        free(map->colors);
        return (0);
    }
    ft_strlcpy(map->colors[0], map->ccieling, strlen(map->ccieling) + 1);
    ft_strlcpy(map->colors[1], map->cfloor, strlen(map->cfloor) + 1);
    ft_color_parse(map);
	return (1);
}


void	all_struct_init(t_cub *mlx, t_ray *ray, t_player *player)
{
	mlx->pl = malloc(sizeof(t_player));
	mlx->ray = malloc(sizeof(t_ray));
	player->posx = 50;
	player->posy = 50;
	mlx->pl = player;
	mlx->ray = ray;

	mlx->pl->compass = 0;
	mlx->pl->movespeed = 0.05;
	mlx->pl->rt_s = 0.05;
	mlx->pl->stepx = 0;
	mlx->pl->stepy = 0;
	mlx->pl->dirx = 0;
	mlx->pl->diry = 0;
	mlx->pl->plnx = 0;
	mlx->pl->plny = 0;
	mlx->pl->posx = 0;
	mlx->pl->posy = 0;

	mlx->ray->hit = 0;
	mlx->ray->side = 0;
	mlx->ray->sidedistx = 0;
	mlx->ray->sidedisty = 0;
	mlx->ray->deltadistx = 0;
	mlx->ray->deltadisty = 0;
	mlx->ray->perpwalldist = 0;
	mlx->ray->drawstart = 0;
	mlx->ray->drawend = 0;
	mlx->ray->lineheight = 0;
	mlx->ray->mapx = 0;
	mlx->ray->mapy = 0;
	mlx->ray->camerax = 0;
	mlx->ray->raydirx = 0;
	mlx->ray->raydiry = 0;
	mlx->ray->wallx = 0;
	mlx->ray->texpos = 0;
	mlx->ray->updown = 0;
	mlx->ray->color = 0;

	direction(mlx->pl);
}

void	direction(t_player *player)
{
	if (player->compass == 0)
	{
		player->dirx = -1;
		player->diry = 0;
		player->plnx = 0;
		player->plny = 0.66;
	}
	if (player->compass == 1 || player->compass == 3)
		player->dirx = 0;
	if (player->compass == 1)
	{
		player->dirx = 0;
		player->diry = 1;
		player->plnx = 0.66;
		player->plny = 0;
	}
	else if (player->compass == 2)
	{
		player->dirx = 1;
		player->diry = 0;
		player->plnx = 0;
		player->plny = -0.66;
	}
	else if (player->compass == 3)
	{
		player->dirx = 0;
		player->diry = -1;
		player->plnx = -0.66;
		player->plny = 0;
	}
}

/*
void test_mlx(t_cub *map)
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	int i = 0;
	int j = 0;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 640, 480, WinName);
	img_ptr = mlx_new_image(mlx_ptr, WinWidth, WinHeight);
	map->addr = mlx_get_data_addr(img_ptr, &map->bpp, &map->len, &map->endian);

	while (i < WinHeight)
	{
		j = 0;
		while (j < WinWidth)
		{
			my_mlx_pixel_put(map, j, i, 0x00FF0000);
			j++;
		}
		i++;
	}

	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
}

void my_mlx_pixel_put(t_cub *map, int x, int y, int color)
{
	char *dst;

	dst = map->addr + (y * map->len + x * (map->bpp / 8));
	*(unsigned int *)dst = color;
}
*/