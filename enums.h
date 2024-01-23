#ifndef ENUMS_H
# define ENUMS_H

# ifdef Linux

typedef enum key_map
{
	ON_DESTROY = 36,
	ESC = 65307,
	UP_ARROW = 65362,
	DOWN_ARROW = 65364,
	RIGHT_ARROW = 65363,
	LEFT_ARROW = 65361,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100
}					t_key_map;

# else

typedef enum key_map
{
	ON_DESTROY = 17,
	ESC = 53,
	UP_ARROW = 126,
	DOWN_ARROW = 125,
	RIGHT_ARROW = 124,
	LEFT_ARROW = 123,
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2
}					t_key_map;

# endif

typedef enum colors
{
	RED = 0xFF0000,
	BLUE = 0x0000FF,
	GRN = 0x00FF00,
	WHT = 0xFFFFFF
}		t_colors;

typedef enum e_side
{
	SOUTH=0,
	EAST=1,
	NORTH=2,
	WEST=3
}	t_side;

#endif