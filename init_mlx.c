#include "cub3d.h"

void init_imgs(t_cub *map)
{
    int	xx;
    
	xx = 0;
	map->tex = mlx_xpm_file_to_image(map->mlx, map->texture[0], &map->w, &map->h);
	map->text = (int *)mlx_get_data_addr(map->tex, &map->b, &map->h, &map->w);
	map->tex2 = mlx_xpm_file_to_image(map->mlx, map->texture[1], &map->w, &map->h);
	map->text2 = (int *)mlx_get_data_addr(map->tex2, &map->b, &map->h, &map->w);
    map->tex3 = mlx_xpm_file_to_image(map->mlx, map->texture[2], &map->w, &map->h);
	map->text3 = (int *)mlx_get_data_addr(map->tex3,&map->b, &map->h, &map->w);
	map->tex4 = mlx_xpm_file_to_image(map->mlx, map->texture[3], &map->w, &map->h);
	map->text4 = (int *)mlx_get_data_addr(map->tex4,&map->b, &map->h, &map->w);
    map->buffer = malloc(sizeof(int *) * WinHeight);
	while (xx < WinHeight)
	{
		map->buffer[xx] = malloc(sizeof(int) * WinWidth);
		xx++;
	}
}

int	ray_cast(t_cub *cub, char **map)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	clearbuffer(cub);
	// ft_putstr_fd("alive\n", 2);
	while (x < WinWidth)
	{
		initdrawing(cub, x); //Done
		// ft_putstr_fd("alive\n", 2);
		initdir(cub); //Done
		get_wall_hit(cub, map); //Done
		get_player_pos(cub, map, &i); //Done
		get_walls(cub, y, x, i); //Done
		get_floor_ceil(cub, y, x); //Done
		x++;
	}
	ft_putstr_fd("alive\n", 2);
	drawall(cub, cub->buffer);
	cub->pl->movespeed = 0.12;
	cub->pl->rt_s = 0.055;
	return (0);
}

void	drawall(t_cub *all, int **buffer)
{
	int	i;
	int	j;
	int	*texture;

	i = 0;
	j = 0;
	all->img = mlx_new_image(all->mlx,WinWidth, WinHeight);
	texture = (int *)mlx_get_data_addr(all->img, &all->b,&all->w, &all->h);
	while (j < WinHeight)
	{
		i = 0;
		while (i < WinWidth)
		{
			texture[j * WinWidth + i] = buffer[j][i];
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(all->mlx,all->win, all->img, 0, 0);
	mlx_destroy_image(all->mlx, all->img);
}

void	clearbuffer(t_cub *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < WinHeight)
	{
		j = 0;
		while (j < WinWidth)
		{
			map->buffer[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	initdrawing(t_cub *cub, int x)
{
	cub->ray->camerax = ((2 * x) / ((double)WinWidth - 1));
	ft_putstr_fd("aqqlive\n", 2);
	cub->ray->raydirx = cub->pl->dirx + cub->pl->plnx * cub->ray->camerax;
	cub->ray->raydiry = cub->pl->diry + cub->pl->plny * cub->ray->camerax;
	cub->ray->mapx = (int)cub->pl->posx;
	cub->ray->mapy = (int)cub->pl->posy;
	if (cub->ray->raydirx == 0)
		cub->ray->deltadistx = 1e30;
	else
		cub->ray->deltadistx = fabs(1 / cub->ray->raydirx);
	if (cub->ray->raydiry == 0)
		cub->ray->deltadisty = 1e30;
	else
		cub->ray->deltadisty = fabs(1 / cub->ray->raydiry);
	cub->ray->hit = 0;
}

void	initdir(t_cub *cub)
{
	if (cub->ray->raydirx < 0)
	{
		cub->pl->stepx = -1;
		cub->ray->sidedistx = (cub->pl->posx - cub->ray->mapx) * cub->ray->deltadistx;
	}
	else
	{
		cub->pl->stepx = 1;
		cub->ray->sidedistx = (cub->ray->mapx + 1.0 - cub->pl->posx) * cub->ray->deltadistx;
	}
	if (cub->ray->raydiry < 0)
	{
		cub->pl->stepy = -1;
		cub->ray->sidedisty = (cub->pl->posy - cub->ray->mapy) * cub->ray->deltadisty;
	}
	else
	{
		cub->pl->stepy = 1;
		cub->ray->sidedisty = (cub->ray->mapy + 1.0 - cub->pl->posy) * cub->ray->deltadisty;
	}
}

void	get_wall_hit(t_cub *cub, char **map)
{
	// printf("map[cub->ray->mapx][cub->ray->mapy] %c\n", map[cub->ray->mapx][cub->ray->mapy]);
	while (cub->ray->hit == 0 && map[cub->ray->mapx][cub->ray->mapy])
	{
		// printf("hhds\n");
		if (cub->ray->sidedistx < cub->ray->sidedisty)
		{
			// printf("hhdswe = %d\n", cub->pl->stepx);
			cub->ray->sidedistx += cub->ray->deltadistx;
			cub->ray->mapx += cub->pl->stepx;
			cub->ray->side = 0;
		}
		else
		{
			// printf("delta y = %f\n", cub->ray->sidedisty);
			cub->ray->sidedisty += cub->ray->deltadisty;
			// printf("step y = %d\n", cub->pl->stepy);
			cub->ray->mapy += cub->pl->stepy;
			if (cub->ray->mapy < 0)
				cub->ray->mapy *= -1;
			cub->ray->side = 1;
		}
		if (cub->ray->mapy < 0)
				cub->ray->mapy *= -1;
		if (cub->ray->mapx < 0)
				cub->ray->mapx *= -1;
		// printf("y = %d\n", cub->ray->mapy);
		// printf("x = %d\n", cub->ray->mapx);
		if (map[cub->ray->mapx][cub->ray->mapy] != '0' &&
				map[cub->ray->mapx][cub->ray->mapy] != 'P')
			cub->ray->hit = 1;
	}
}

void	get_player_pos(t_cub *cub, char **map, int *ii)
{
	extracheck(cub);
	if (cub->drawend >= WinHeight)
		cub->drawend = WinHeight - 1;
	if (cub->ray->side == 0 && map[(int)cub->ray->mapx]
		[(int)cub->ray->mapy] == '1')
	{
		cub->ray->wallx = cub->pl->posy + cub->ray->perpwalldist * cub->ray->raydiry;
		if (cub->ray->raydirx > 0)
			*ii = 2;
		else
			*ii = 1;
	}
	else
	{
		cub->ray->wallx = cub->pl->posx + cub->ray->perpwalldist * cub->ray->raydirx;
		if (cub->ray->raydiry > 0)
			*ii = 3;
		else
			*ii = 4;
	}
}

void	extracheck(t_cub *cub)
{
	if (cub->ray->side == 0)
		cub->ray->perpwalldist = (cub->ray->sidedistx - cub->ray->deltadistx);
	else
		cub->ray->perpwalldist = (cub->ray->sidedisty - cub->ray->deltadisty);
	cub->lineheight = (int)(WinHeight / cub->ray->perpwalldist);
	cub->drawstart = -cub->lineheight / 2 + ((WinHeight / 2) + cub->ray->updown);
	if (cub->drawstart < 0)
		cub->drawstart = 0;
	cub->drawend = cub->lineheight / 2 + ((WinHeight / 2) + cub->ray->updown);
}

void	get_walls(t_cub *cub, int y, int x, int ii)
{
	cub->ray->wallx = (double)cub->ray->wallx - (int)cub->ray->wallx;
	cub->texx = (int)(cub->ray->wallx * (double)64);
	if (cub->ray->side == 0 && cub->ray->raydirx > 0)
		cub->texx = 64 - cub->texx - 1;
	if (cub->ray->side == 1 && cub->ray->raydiry < 0)
		cub->texx = 64 - cub->texx - 1;
	cub->ray->step = 1.0 * 64 / cub->lineheight;
	cub->ray->texpos = (cub->drawstart - ((WinHeight / 2)
				+ cub->ray->updown) + cub->lineheight / 2) * cub->ray->step;
	y = cub->drawstart;
	while (y < cub->drawend)
	{
		cub->texy = (int)cub->ray->texpos & (64 - 1);
		cub->ray->texpos += cub->ray->step;
		gettexture(cub, ii);
		cub->buffer[y][x] = cub->ray->color;
		y++;
	}
}

void	gettexture(t_cub *cub, int ii)
{
	if (ii == 1)
		cub->ray->color = mlx_get_color_value(cub->mlx, cub->text[(64 * cub->texy) + cub->texx]);
	else if (ii == 2)
		cub->ray->color = mlx_get_color_value(cub->mlx, cub->text2[(64 * cub->texy) + cub->texx]);
	else if (ii == 3)
		cub->ray->color = mlx_get_color_value(cub->mlx, cub->text3[(64 * cub->texy) + cub->texx]);
	else if (ii == 4)
		cub->ray->color = mlx_get_color_value(cub->mlx, cub->text4[(64 * cub->texy) + cub->texx]);
}

void	get_floor_ceil(t_cub *all, int y, int x)
{
	while (y < all->drawstart)
	{
		if (all->drawstart < 0 || all->drawstart > all->drawend)
			break ;
		all->buffer[y][x] = all->ccolor;
		y++;
	}
	y = all->drawend;
	fill_ceil(all, y, x);
	y = 0;
	while (y < WinHeight)
	{
		if (all->buffer[y][x] == 0 && all->ray->updown > 0 && (y < all->drawstart || y > all->drawend))
			all->buffer[y][x] = all->ccolor;
		if (all->buffer[y][x] == 0 && all->ray->updown < 0 && (y < all->drawstart || y > all->drawend))
			all->buffer[y][x] = all->fcolor;
		y++;
	}
}

void	fill_ceil(t_cub *all, int y, int x)
{
	while (y < WinHeight)
	{
		if (all->drawend < 0 || all->drawend < all->drawstart)
			break ;
		all->buffer[y][x] = all->fcolor;
		y++;
	}
}

char	*ft_rgb_to_hex(t_cub *all, char *rgb, size_t i)
{
	char	*color;
	int		tmp;

	color = ft_strdup("");
	tmp = 255;
	while (rgb[i] == ' ')
		i++;
	while (rgb[i])
	{
		tmp = ft_atoi_index(all, rgb, i, 6);
		color = ft_strjoin(color, ft_convert_base(ft_itoa(tmp), DEC, HEX));
		while (rgb[i] && ft_isdigit(rgb[i]))
			i++;
		if (rgb[i] && rgb[i] == ',')
			i++;
	}
	return (color);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int	i;
	int	j;
	int	fnb;
	int	sign;

	i = 0;
	fnb = 0;
	sign = 0;
	while (nbr[i] && (nbr[i] == ' ' || nbr[i] == '\f'
			|| nbr[i] == '\n' || nbr[i] == '\t' || nbr[i] == '\v'))
		i++;
	while (nbr[i] && (nbr[i] == '+' || nbr[i] == '-'))
		if (nbr[i++] == '-')
			sign++;
	while (nbr[i] && ft_strchr(base_from, nbr[i]))
	{
		j = 0;
		while (base_from[j])
			if (base_from[j++] == nbr[i])
				fnb = fnb * ft_strlen(base_from) + j - 1;
		i++;
	}
	return (ft_put_nbr(fnb, base_to, sign, -1));
}

char	*ft_put_nbr(int nbr, char *base, int sign, int i)
{
	int		nbase;
	int		pbase;
	char	*num;

	nbase = ft_strlen(base);
	pbase = ft_lnbr(nbr, nbase);
	if (sign % 2 != 0 && nbr != 0)
	{
		num = malloc((pbase + 2) * sizeof(char));
		if (!num)
			return (0);
		while (++i < pbase + 2)
			num[i] = '\0';
		num[0] = '-';
	}
	else
	{
		num = malloc((pbase + 1) * sizeof(char));
		if (!num)
			return (0);
		while (++i < pbase + 1)
			num[i] = '\0';
	}
	ft_putnbr_base(nbr, nbase, num, base);
	return (num);
}

int	ft_lnbr(int nbr, int base_lenght)
{
	int	x;
	int	pbase;

	if (nbr == 0)
		return (1);
	x = 1;
	pbase = 1;
	while (x <= nbr)
	{
		x = x * base_lenght;
		pbase++;
	}
	return (pbase - 1);
}

void	ft_putnbr_base(int nbr, int nbase, char *num_base, char *base)
{
	if (nbr >= nbase)
	{
		ft_putnbr_base((nbr / nbase), nbase, num_base, base);
	}
	ft_char(num_base, base[nbr % nbase]);
}

char	*ft_char(char *dest, char src)
{
	unsigned int	i;

	i = 0;
	while (dest[i])
		i++;
	dest[i++] = src;
	dest[i] = '\0';
	return (dest);
}

void	ft_color_parse(t_cub *all)
{
	char	*fc;
	char	*cc;

	ft_color_chars_init_checker(all);
	fc = ft_convert_base(ft_rgb_to_hex(all, all->colors[0], 0), HEX, DEC);
	cc = ft_convert_base(ft_rgb_to_hex(all, all->colors[1], 0), HEX, DEC);
	all->fcolor = ft_atoi_index(all, fc, 0, 6);
	all->ccolor = ft_atoi_index(all, cc, 0, 6);
	printf("fcolor = %ld\n", all->fcolor);
	printf("ccolor = %ld\n", all->ccolor);
	free(fc);
	free(cc);
}

void	ft_color_chars_init_checker(t_cub *all)
{
	printf("all->colors[0] = %s\n", all->colors[0]);
	printf("all->colors[1] = %s\n", all->colors[1]);
	if (all->colors[0][0] != 'F' || all->colors[1][0] != 'C'
		|| all->colors[0][1] != ' ' || all->colors[1][1] != ' ')
		ft_error(all, 6);
}

void	ft_color_chars_checker(t_cub *all, size_t i, size_t a, int comma)
{
	ft_color_chars_init_checker(all);
	while (a < 2)
	{
		comma = 0;
		i = 2;
		while (all->colors[a][i] == ' ')
			i++;
		while (all->colors[a][i])
		{
			if (!ft_isdigit(all->colors[a][i]))
				ft_error(all, 6);
			if (ft_atoi_index(all, all->colors[a], i, 6) > 255
				|| ft_atoi_index(all, all->colors[a], i, 6) < 0)
				ft_error(all, 6);
			while (all->colors[a][i] && ft_isdigit(all->colors[a][i]))
				i++;
			if (all->colors[a][i] && all->colors[a][i] == ',')
				comma++;
			if (all->colors[a][i] &&
				(all->colors[a][i] != ',' || !ft_isdigit(all->colors[a][++i])))
				ft_error(all, 6);
		}
		if (++a && comma != 2)
			ft_error(all, 6);
	}
}

size_t	ft_atoi_index(t_cub *all, const char *str, size_t i, int error)
{
	size_t	nb;

	nb = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	while (ft_isdigit(str[i]))
	{
		if (nb >= 9223372036854775807)
			ft_error(all, error);
		nb = nb * 10 + str[i++] - 48;
	}
	return (nb);
}

void	ft_error(t_cub *all, int error)
{
	// printf("hii\n");
	// ft_putstr_fd(RED, 2);
	printf("all->colors[0] = %s\n", all->colors[0]);
	printf("all->colors[1] = %s\n", all->colors[1]);
	if (error != 0)
		ft_putstr_fd("Error: ", 2);
	if (error == 2)
		ft_putstr_fd("Invalid map extension\n", 2);
	else if (error == 3)
		ft_putstr_fd("File reading failed\n", 2);
	else if (error == 4)
		ft_putstr_fd("Memory allocation failed\n", 2);
	else if (error == 5)
		ft_putstr_fd("Invalid Map\n", 2);
	else if (error == 6)
		ft_putstr_fd("Invalid Color\n", 2);
	else if (error == 7)
		ft_putstr_fd("Invalid chars in map\n", 2);
	else if (error == 8)
		ft_putstr_fd("Unclosed map\n", 2);
	else if (error == 9)
		ft_putstr_fd("Unclosed map on space\n", 2);
	ft_putstr_fd(RESET, 2);
	ft_destroy_free(all); //free all mlx but keep for later
}

void	ft_free_all(t_cub *all)
{
	if (all->xmap)
		free(all->xmap);
	// if (all->mapl)
	// 	free(all->mapl);
	// ft_free_arr(all->splmap);
	// ft_free_arr(all->textures);
	// ft_free_arr(all->colors);
	// ft_free_arr(all->map);
}

int	ft_destroy_free(t_cub *all)
{
	int	i;

	i = -1;
	if (all->win)
		mlx_destroy_window(all->mlx, all->win);
	if (all->tex)
		mlx_destroy_image(all->mlx, all->tex);
	if (all->tex2)
		mlx_destroy_image(all->mlx, all->tex2);
	if (all->tex3)
		mlx_destroy_image(all->mlx, all->tex3);
	if (all->tex4)
		mlx_destroy_image(all->mlx, all->tex4);
	if (all->buffer)
		while (++i < WinHeight)
			free(all->buffer[i]);
	free(all->buffer);
	ft_free_all(all);
	exit(0);
}













// || mlx part || 

/*
void	mlx(t_cub *cub)
{
    cub->mlx = mlx_init();
    cub->win = mlx_new_window(cub->mlx, WinWidth, WinHeight, WinName);
    cub->img = mlx_new_image(cub->mlx, WinWidth, WinHeight);
    cub->addr = mlx_get_data_addr(cub->img, &cub->bpp, &cub->len, &cub->endian);

    printf("seg1\n");
    init_texture(cub);
    printf("seg2\n");
    init_player(cub);
    printf("seg3\n");
    t_ray ray;
    init_ray(cub, &ray);
    printf("seg4\n");
    mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
    mlx_hook(cub->win, 2, 1L << 0, key_press, cub);
    mlx_hook(cub->win, 3, 1L << 1, key_release, cub);
    mlx_hook(cub->win, 17, 1L << 17, close_win, cub);
    mlx_loop_hook(cub->mlx, render_next_frame, cub);
    mlx_loop(cub->mlx);   
}

void init_texture(t_cub *cub)
{
    cub->texture[0].img = mlx_xpm_file_to_image(cub->mlx, cub->path->no, &cub->texture[0].width, &cub->texture[0].height);
    cub->texture[0].addr = mlx_get_data_addr(cub->texture[0].img, &cub->texture[0].bpp, &cub->texture[0].len, &cub->texture[0].endian);
    cub->texture[1].img = mlx_xpm_file_to_image(cub->mlx, cub->path->so, &cub->texture[1].width, &cub->texture[1].height);
    cub->texture[1].addr = mlx_get_data_addr(cub->texture[1].img, &cub->texture[1].bpp, &cub->texture[1].len, &cub->texture[1].endian);
    cub->texture[2].img = mlx_xpm_file_to_image(cub->mlx, cub->path->ea, &cub->texture[2].width, &cub->texture[2].height);
    cub->texture[2].addr = mlx_get_data_addr(cub->texture[2].img, &cub->texture[2].bpp, &cub->texture[2].len, &cub->texture[2].endian);
    cub->texture[3].img = mlx_xpm_file_to_image(cub->mlx, cub->path->we, &cub->texture[3].width, &cub->texture[3].height);
    cub->texture[3].addr = mlx_get_data_addr(cub->texture[3].img, &cub->texture[3].bpp, &cub->texture[3].len, &cub->texture[3].endian);
}

int key_press(int keycode, t_cub *cub)
{
    if (keycode == 13)
        cub->N = 1;
    if (keycode == 1)
        cub->S = 1;
    if (keycode == 0)
        cub->W = 1;
    if (keycode == 2)
        cub->E = 1;
    if (keycode == 123)
        cub->L = 1;
    if (keycode == 124)
        cub->R = 1;
    if (keycode == 53)
        cub->esc = 1;
    return (0);
}

int key_release(int keycode, t_cub *cub)
{
    if (keycode == 13)
        cub->N = 0;
    if (keycode == 1)
        cub->S = 0;
    if (keycode == 0)
        cub->W = 0;
    if (keycode == 2)
        cub->E = 0;
    if (keycode == 123)
        cub->L = 0;
    if (keycode == 124)
        cub->R = 0;
    if (keycode == 53)
        cub->esc = 0;
    return (0);
}

int close_win(t_cub *cub)
{
    mlx_destroy_window(cub->mlx, cub->win);
    exit(0);
    return (0);
}

static void move_forward(t_cub *cub)
{
    if (cub->map[(int)(cub->py + cub->diry * cub->movespeed)][(int)cub->px] == '0')
        cub->py += cub->diry * cub->movespeed;
    if (cub->map[(int)cub->py][(int)(cub->px + cub->dirx * cub->movespeed)] == '0')
        cub->px += cub->dirx * cub->movespeed;
}

static void move_backward(t_cub *cub)
{
    if (cub->map[(int)(cub->py - cub->diry * cub->movespeed)][(int)cub->px] == '0')
        cub->py -= cub->diry * cub->movespeed;
    if (cub->map[(int)cub->py][(int)(cub->px - cub->dirx * cub->movespeed)] == '0')
        cub->px -= cub->dirx * cub->movespeed;
}

static void move_left(t_cub *cub)
{
    if (cub->map[(int)(cub->py - cub->dirx * cub->movespeed)][(int)cub->px] == '0')
        cub->py -= cub->dirx * cub->movespeed;
    if (cub->map[(int)cub->py][(int)(cub->px + cub->diry * cub->movespeed)] == '0')
        cub->px += cub->diry * cub->movespeed;
}

static void move_right(t_cub *cub)
{
    if (cub->map[(int)(cub->py + cub->dirx * cub->movespeed)][(int)cub->px] == '0')
        cub->py += cub->dirx * cub->movespeed;
    if (cub->map[(int)cub->py][(int)(cub->px - cub->diry * cub->movespeed)] == '0')
        cub->px -= cub->diry * cub->movespeed;
}

static void rotate_left(t_cub *cub)
{
    double olddirx = cub->dirx;
    cub->dirx = cub->dirx * cos(cub->rotspeed) - cub->diry * sin(cub->rotspeed);
    cub->diry = olddirx * sin(cub->rotspeed) + cub->diry * cos(cub->rotspeed);
    double oldplanex = cub->planex;
    cub->planex = cub->planex * cos(cub->rotspeed) - cub->planey * sin(cub->rotspeed);
    cub->planey = oldplanex * sin(cub->rotspeed) + cub->planey * cos(cub->rotspeed);
}

static void rotate_right(t_cub *cub)
{
    double olddirx = cub->dirx;
    cub->dirx = cub->dirx * cos(-cub->rotspeed) - cub->diry * sin(-cub->rotspeed);
    cub->diry = olddirx * sin(-cub->rotspeed) + cub->diry * cos(-cub->rotspeed);
    double oldplanex = cub->planex;
    cub->planex = cub->planex * cos(-cub->rotspeed) - cub->planey * sin(-cub->rotspeed);
    cub->planey = oldplanex * sin(-cub->rotspeed) + cub->planey * cos(-cub->rotspeed);
}

int render_next_frame(t_cub *cub)
{
    if (cub->N)
        move_forward(cub);
    if (cub->S)
        move_backward(cub);
    if (cub->W)
        move_left(cub);
    if (cub->E)
        move_right(cub);
    if (cub->L)
        rotate_left(cub);
    if (cub->R)
        rotate_right(cub);
    if (cub->esc)
        close_win(cub);
    return (0);
}

static void my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
    char *dst;

    dst = cub->addr + (y * cub->len + x * (cub->bpp / 8));
    *(unsigned int *)dst = color;
}

void draw(t_cub *cub)
{
    int x = 0;
    int y = 0;
    int color = 0;

    while (x < WinWidth)
    {
        y = 0;
        while (y < WinHeight)
        {
            color = 0x000000;
            if (x < WinWidth / 2)
                color = 0x00FF00;
            if (y < WinHeight / 2)
                color = color | 0xFF0000;
            if (x > WinWidth / 2)
                color = color | 0x0000FF;
            if (y > WinHeight / 2)
                color = color | 0xFFFF00;
            my_mlx_pixel_put(cub, x, y, color);
            y++;
        }
        x++;
    }
}


void init_player(t_cub *cub)
{
    cub->px = 22;
    cub->py = 12;
    cub->dirx = -1;
    cub->diry = 0;
    cub->planex = 0;
    cub->planey = 0.66;
    cub->movespeed = 0.05;
    cub->rotspeed = 0.05;
}

static void init_ray1(t_cub *cub, t_ray *ray, int x)
{
    printf("seg5\n");
    ray->camerax = 2 * x / (double)WinWidth - 1;
    ray->raydirx = cub->dirx + cub->planex * ray->camerax;
    ray->raydiry = cub->diry + cub->planey * ray->camerax;
    ray->mapx = (int)cub->px;
    ray->mapy = (int)cub->py;
    ray->deltadistx = fabs(1 / ray->raydirx);
    ray->deltadisty = fabs(1 / ray->raydiry);
    ray->hit = 0;
}

static void init_ray2(t_cub *cub, t_ray *ray)
{
    printf("seg6\n");
    if (ray->raydirx < 0)
    {
        ray->stepx = -1;
        ray->sidedistx = (cub->px - ray->mapx) * ray->deltadistx;
    }
    else
    {
        ray->stepx = 1;
        ray->sidedistx = (ray->mapx + 1.0 - cub->px) * ray->deltadistx;
    }
    if (ray->raydiry < 0)
    {
        ray->stepy = -1;
        ray->sidedisty = (cub->py - ray->mapy) * ray->deltadisty;
    }
    else
    {
        ray->stepy = 1;
        ray->sidedisty = (ray->mapy + 1.0 - cub->py) * ray->deltadisty;
    }
}

static void init_ray3(t_cub *cub, t_ray *ray)
{
    printf("seg7\n");
    while (ray->hit == 0)
    {
        if (ray->sidedistx < ray->sidedisty)
        {
            ray->sidedistx += ray->deltadistx;
            ray->mapx += ray->stepx;
            ray->side = 0;
        }
        else
        {
            ray->sidedisty += ray->deltadisty;
            ray->mapy += ray->stepy;
            ray->side = 1;
        }
        printf("ray->mapx = %d, ray->mapy = %d\n", ray->mapx, ray->mapy);
        if (cub->xmap[ray->mapx][ray->mapy] == '1')
            ray->hit = 1;
    }
}

static void init_ray4(t_cub *cub, t_ray *ray)
{
    printf("seg8\n");
    if (ray->side == 0)
        ray->perpwalldist = (ray->mapx - cub->px + (1 - ray->stepx) / 2) / ray->raydirx;
    else
        ray->perpwalldist = (ray->mapy - cub->py + (1 - ray->stepy) / 2) / ray->raydiry;
    ray->lineheight = (int)(WinHeight / ray->perpwalldist);
    ray->drawstart = -ray->lineheight / 2 + WinHeight / 2;
    if (ray->drawstart < 0)
        ray->drawstart = 0;
    ray->drawend = ray->lineheight / 2 + WinHeight / 2;
    if (ray->drawend >= WinHeight)
        ray->drawend = WinHeight - 1;
}

static void init_ray5(t_cub *cub, t_ray *ray)
{
    printf("seg9\n");
    if (ray->side == 0)
    {
        ray->wallx = cub->py + ray->perpwalldist * ray->raydiry;
        ray->wallx = cub->px + ray->perpwalldist * ray->raydirx;
    }
    ray->wallx -= floor(ray->wallx);
    ray->texx = (int)(ray->wallx * (double)TexWidth);
    if (ray->side == 0 && ray->raydirx > 0)
        ray->texx = TexWidth - ray->texx - 1;
    if (ray->side == 1 && ray->raydiry < 0)
        ray->texx = TexWidth - ray->texx - 1;
    ray->step = 1.0 * TexHeight / ray->lineheight;
    ray->texpos = (ray->drawstart - WinHeight / 2 + ray->lineheight / 2) * ray->step;
}

static void init_ray6(t_cub *cub, t_ray *ray)
{
    printf("seg10\n");
    int y = ray->drawstart;

    while (y < ray->drawend)
    {
        ray->texy = (int)ray->texpos & (TexHeight - 1);
        ray->texpos += ray->step;
        int color = cub->texture[ray->side].addr[TexHeight * ray->texy + ray->texx];
        if (ray->side == 1)
            color = (color >> 1) & 8355711;
        cub->addr[y * cub->len + ray->x * (cub->bpp / 8)] = color;
        y++;
    }
}

void init_ray(t_cub *cub, t_ray *ray)
{
    int x = 0;

    while (x < WinWidth)
    {
        init_ray1(cub, ray, x);
        init_ray2(cub, ray);
        init_ray3(cub, ray);
        init_ray4(cub, ray);
        init_ray5(cub, ray);
        init_ray6(cub, ray);
        x++;
    }
}
*/