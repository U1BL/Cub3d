#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_cub	map;
	t_player player;
	t_ray	ray;
	// t_all	all;
	// t_var vars;
	map = (t_cub){0};

	all_struct_init(&map, &ray, &player);
	if (!(parse_check(argc, argv, &map)))
	{
		ft_putstr_fd("RED", 2);
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(RESET, 2);
		exit(0);
	}
	map.mlx = mlx_init();
	map.win = mlx_new_window(map.mlx, WinWidth, WinHeight, "cub3d");
	init_imgs(&map);
	ray_cast(&map, map.xmap);
	ft_putstr_fd("alive\n", 2);
	mlx_hook(map.win, 2, 1L << 0, key, &map);
	mlx_hook(map.win, 17, 1L << 5, ft_destroy_free, &map);
	mlx_loop(map.mlx);

	return (0);
}