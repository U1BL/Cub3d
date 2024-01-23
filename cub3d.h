#ifndef CUB3D_H
# define CUB3D_H

// #include <GL/glut.h>
// #include <GL/glu.h>
// #include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
#include "Get_Next_Line/get_next_line.h"
#include "./mlx/mlx.h"
#include "enums.h"
#include <stdbool.h>

// # define UP_ARROW 126
// # define DOWN_ARROW 125
// # define RIGHT_ARROW 124
// # define LEFT_ARROW 123
// # define ESC 53

// # define KEY_W 13
// # define KEY_A 0
// # define KEY_S 1
// # define KEY_D 2

// # define RED "\033[1;31m"
# define RESET "\033[0m"

# define HEX "0123456789ABCDEF"
# define DEC "0123456789"

#define WinWidth 1000
#define WinHeight 800
#define MapWidth 24
#define MapHeight 24
#define TexWidth 64
#define TexHeight 64
#define WinName "cub3d"


typedef struct s_path
{
	char *no;
	char *so;
	char *we;
	char *ea;
}t_path;

typedef struct s_texture
{
	int		width;
	int		height;
	int		len;
	int		bpp;
	int		sl;
	int		endian;
	char	*dir;
	void	*img;
	char	*addr;
}t_texture;


typedef struct s_ray
{
	int		hit;
	int		side;
	int		mapx;
	int		mapy;
	double	step;
	double	wallx;
	int		color;
	double	texpos;
	int		updown;
	int		drawend;
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		drawstart;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	int		lineheight;
	double	deltadisty;
	double	perpwalldist;
}t_ray;

typedef struct s_vars
{
	int p;
	int	i;
	int	j;
	int k;
	int	len;
	int flag;
}t_var;

typedef struct s_player
{
	int		compass;
	double	dirx;
	double	diry;
	double	posx;
	double	posy;
	double	plnx;
	double	plny;
	int		stepx;
	int		stepy;
	double	rt_s;
	double	movespeed;
}t_player;

typedef struct	s_cub
{
	char *texture[5];
	t_path		*path;
	t_ray 		*ray;
	t_player	*pl;
	int			drawend;
	int			drawstart;
	int			lineheight;
    char		**map;
	char		**xmap;
	char		**dup_map;
	char		*no_tmp;
	char		*so_tmp;
	char		*we_tmp;
	char		*ea_tmp;
	char		*floor_tmp;
	char		*cieling_tmp;
	char		*addr;
	char		*cfloor;
	long int	ccolor;
	long int	fcolor;
	char		*ccieling;
	char		**colors;
	void		*win;
	void		*mlx;
	void		*img;
	int			texx;
	int			texy;
	void		*tex;
	int			*text;
	void		*tex2;
	int			*text2;
	void		*tex3;
	int			*text3;
	void		*tex4;
	int			*text4;
	int			**buffer;
	int			b;
	int			h;
	int			w;
	int			len;
	int			py;
	int			px;
	char		dir;
	int			sprite;
	int			*cieling;
	int			*floor;
	int			E;
	int			S;
	int			N;
	int			W;
	int			L;
	int			R;
	int			esc;
	int			bpp;
	int			sl;
	int			endian;
	int			movespeed;
	int			rotspeed;
	int			dirx;
	int			diry;
	int			planex;
	int			planey;
	int			x;
	int			y;
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	int			hit;
}t_cub;

typedef struct s_all
{
	t_path *path;
	t_texture *texture;
	t_cub *cub;
	// t_vars *vars;
	t_player *player;
	t_ray *ray;
} t_all;

//parsing functions
int	parse_check(int argc, char *argv[], t_cub *map);
int	check_file(char *file);
int	init_map(t_cub *map, char *k);
int store_textures(t_cub *map);
int textures(t_cub *map);
int store_rgb(t_cub *map);
int rgb(t_cub *map);
int check_rgb(t_cub *map);
int check_map(t_cub *map, int map_len);
int maps(t_cub *map);
void print_map(t_cub *map);
int store_map(t_cub *map);
int render_next_frame(t_cub *map);


//mlx functions

void	mlx(t_cub *cub);
int		key_press(int keycode, t_cub *cub);
int		key_release(int keycode, t_cub *cub);
int		close_win(t_cub *cub);
void	init_texture(t_cub *cub);
void	init_player(t_cub *cub);
void	init_ray(t_cub *cub, t_ray *ray);
void	init_mlx(t_cub *cub);

void test_mlx(t_cub *map);
void my_mlx_pixel_put(t_cub *map, int x, int y, int color);

//copied one
void	direction(t_player *player);
void 	init_imgs(t_cub *map);
void	clearbuffer(t_cub *map);
int		ray_cast(t_cub *all, char **map);
void	all_struct_init(t_cub *mlx, t_ray *ray, t_player *player);
void	initdrawing(t_cub *cub, int x);
void	get_wall_hit(t_cub *cub, char **map);
void	initdir(t_cub *cub);
void	gettexture(t_cub *cub, int ii);
void	get_walls(t_cub *cub, int y, int x, int ii);
void	extracheck(t_cub *cub);
void	get_player_pos(t_cub *cub, char **map, int *ii);
void	get_floor_ceil(t_cub *all, int y, int x);
void	fill_ceil(t_cub *all, int y, int x);
char	*ft_rgb_to_hex(t_cub *all, char *rgb, size_t i);
char	*ft_convert_base(char *nbr, char *base_from, char *base_to);
char	*ft_put_nbr(int nbr, char *base, int sign, int i);
int		ft_lnbr(int nbr, int base_lenght);
void	ft_putnbr_base(int nbr, int nbase, char *num_base, char *base);
char	*ft_char(char *dest, char src);
void	ft_color_parse(t_cub *all);
size_t	ft_atoi_index(t_cub *all, const char *str, size_t i, int error);
void	ft_error(t_cub *all, int error);
int		ft_destroy_free(t_cub *all);
void	drawall(t_cub *all, int **buffer);
char	**_2d_array_dup(char **arr, size_t start, size_t size);
void	ft_color_chars_init_checker(t_cub *all);
void	ft_color_chars_checker(t_cub *all, size_t i, size_t a, int comma);

//keys
void	key13_1(t_cub *all, int keycode);
void	key0_2(t_cub *all, int keycode);
void	key124_123(t_cub *a, int keycode);
int		key(int keycode, t_cub *all);
int	check_wall_collision(t_cub *all, char c);
//////
char *store_rgb_string(int r, int g, int b);

//////
void free_strings(char **str);
int	check_invalid_path(t_cub *map_line, int y, int x);
void invalid(t_cub *tmp, int i, int j);
void map_area(t_cub *coordinate);
void map_draw(t_cub *coordinate);
int fill_map(t_cub *map_line, char *file);
int	exit_game(t_cub *vars);
int	moves(int key, t_cub *vars);
void	free_tools(t_cub *p);


#endif