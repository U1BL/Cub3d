#include "cub3d.h"

void	key13_1(t_cub *all, int keycode)
{
	if (keycode == 13)
	{
		if (check_wall_collision(all, 'x'))
			all->pl->posx += all->pl->dirx * all->pl->movespeed;
		if (check_wall_collision(all, 'y'))
			all->pl->posy += all->pl->diry * all->pl->movespeed;
	}
	else if (keycode == 1)
	{
		if (all->xmap[(int)(all->pl->posx - all->pl->dirx * all->pl->movespeed)][(int)(all->pl->posy)] != '1')
			all->pl->posx -= all->pl->dirx * all->pl->movespeed;
		if (all->xmap[(int)(all->pl->posx)][(int)(all->pl->posy- all->pl->diry * all->pl->movespeed)] != '1')
			all->pl->posy -= all->pl->diry * all->pl->movespeed;
	}
}

void	key0_2(t_cub *all, int keycode)
{
	if (keycode == KEY_A)
	{
		if (all->xmap[(int)(all->pl->posx - all->pl->diry* all->pl->movespeed)][(int)(all->pl->posy)] != '1')
			all->pl->posx -= all->pl->diry * all->pl->movespeed;
		if (all->xmap[(int)(all->pl->posx)][(int)(all->pl->posy+ all->pl->dirx * all->pl->movespeed)] != '1')
			all->pl->posy += all->pl->dirx * all->pl->movespeed;
	}
	else if (keycode == KEY_D)
	{
		if (all->xmap[(int)(all->pl->posx + all->pl->diry* all->pl->movespeed)][(int)(all->pl->posy)] != '1')
			all->pl->posx += all->pl->diry * all->pl->movespeed;
		if (all->xmap[(int)(all->pl->posx)][(int)(all->pl->posy- all->pl->dirx * all->pl->movespeed)] != '1')
			all->pl->posy -= all->pl->dirx * all->pl->movespeed;
	}
}

void	key124_123(t_cub *a, int keycode)
{
	double	odx;
	double	opx;

	if (keycode == 124)
	{
		odx = a->pl->dirx;
		opx = a->pl->plnx;
		a->pl->dirx = a->pl->dirx * cos(-a->pl->rt_s)- a->pl->diry * sin(-a->pl->rt_s);
		a->pl->diry = odx * sin(-a->pl->rt_s) + a->pl->diry * cos(-a->pl->rt_s);
		a->pl->plnx = a->pl->plnx * cos(-a->pl->rt_s)- a->pl->plny * sin(-a->pl->rt_s);
		a->pl->plny = opx * sin(-a->pl->rt_s) + a->pl->plny * cos(-a->pl->rt_s);
	}
	else if (keycode == 123)
	{
		odx = a->pl->dirx;
		opx = a->pl->plnx;
		a->pl->dirx = a->pl->dirx * cos(a->pl->rt_s)- a->pl->diry * sin(a->pl->rt_s);
		a->pl->diry = odx * sin(a->pl->rt_s) + a->pl->diry * cos(a->pl->rt_s);
		a->pl->plnx = a->pl->plnx * cos(a->pl->rt_s)- a->pl->plny * sin(a->pl->rt_s);
		a->pl->plny = opx * sin(a->pl->rt_s) + a->pl->plny * cos(a->pl->rt_s);
	}
}

int	key(int keycode, t_cub *all)
{
	if (keycode == ESC)
		ft_destroy_free(all);
	if (keycode == KEY_W || keycode == KEY_S)
		key13_1(all, keycode);
	if (keycode == KEY_A || keycode == KEY_D)
		key0_2(all, keycode);
	if (keycode == UP_ARROW)
		if (all->ray->updown < WinHeight)
			all->ray->updown += 7;
	if (keycode == DOWN_ARROW)
		if ((all->ray->updown * -1) < WinHeight)
			all->ray->updown -= 7;
	if (keycode == RIGHT_ARROW || keycode == LEFT_ARROW)
		key124_123(all, keycode);
	mlx_clear_window(all->mlx, all->win);
	ray_cast(all, all->xmap);
	return (0);
}

int	check_wall_collision(t_cub *all, char c)
{
	double	checker;
	int		flag;

	flag = 0;
	checker = 0.1;
	while (checker <= all->pl->movespeed)
	{
		if (c == 'y')
		{
			if (all->xmap[(int)(all->pl->posx)][(int)
				(all->pl->posy + all->pl->diry * checker)] == '1')
				return (0);
		}
		else if (c == 'x')
			if (all->xmap[(int)(all->pl->posx + all->pl->dirx
					* all->pl->movespeed)][(int)(all->pl->posy)] == '1')
				return (0);
		checker += 0.1;
		if (checker > all->pl->movespeed && !flag)
		{
			checker = all->pl->movespeed;
			flag = 1;
		}
	}
	return (1);
}