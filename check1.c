#include "cub3d.h"

static int	init_map2(t_cub *map, char *k)
{
	int		fd;
	char	*line;

	fd = open(k, O_RDONLY);
	if (fd < 0)
		return (ft_putendl_fd("Error\nfile error", 2), 0);
	line = get_next_line(fd);
	free(line);
	map->y = 0;
	while (line != NULL)
	{
		line = get_next_line(fd);
		free(line);
		map->y++;
	}
	close(fd);
	map->map = malloc(sizeof(char *) * (map->y + 1));
	map->map[map->y] = NULL;
	if (!map->map)
		return (0);
	return (1);
}

int	init_map(t_cub *map, char *k)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	if (!init_map2(map, k))
		return (0);
	fd = open(k, O_RDONLY);
	if (fd < 0)
		return (0);
	while (i < map->y)
	{
		line = get_next_line(fd);
		map->map[i] = ft_strtrim(line, "\n");
		free(line);
		i++;
	}
	map->map[i] = NULL;
	if (!textures(map) || !rgb(map))
		return (0);
	if (maps(map))
		store_map(map);
	else
		return (0);
	close(fd);
	return (1);
}

int textures(t_cub *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N' && map->map[i][j + 1] == 'O')
			{
				j += 2;
				while (map->map[i][j] == ' ')
					j++;
				if (map->map[i][j] != '\0' && strstr(map->map[i] + j, ".xpm"))
					map->no_tmp = ft_strdup(map->map[i] + j);
			}
			else if (map->map[i][j] == 'S' && map->map[i][j + 1] == 'O')
			{
				j += 2;
				while (map->map[i][j] == ' ')
					j++;
				if (map->map[i][j] != '\0' && strstr(map->map[i] + j, ".xpm"))
					map->so_tmp = ft_strdup(map->map[i] + j);
			}
			else if (map->map[i][j] == 'W' && map->map[i][j + 1] == 'E')
			{
				j += 2;
				while (map->map[i][j] == ' ')
					j++;
				if (map->map[i][j] != '\0' && strstr(map->map[i] + j, ".xpm"))
					map->we_tmp = ft_strdup(map->map[i] + j);
			}
			else if (map->map[i][j] == 'E' && map->map[i][j + 1] == 'A')
			{
				j += 2;
				while (map->map[i][j] == ' ')
					j++;
				if (map->map[i][j] != '\0' && strstr(map->map[i] + j, ".xpm"))
					map->ea_tmp = ft_strdup(map->map[i] + j);
			}
			j++;
		}
		i++;
	}
	// printf("texture path is: %s\n", map->no_tmp);
    // printf("texture path is: %s\n", map->so_tmp);
    // printf("texture path is: %s\n", map->we_tmp);
    // printf("texture path is: %s\n", map->ea_tmp);
	if (!store_textures(map))
		return (printf("Error: Wrong Texture\n"), 0);
	return (1);
}

int rgb(t_cub *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'F' && map->map[i][j + 1] == ' ')
				map->floor_tmp = ft_strdup(map->map[i] + j);
			else if (map->map[i][j] == 'C' && map->map[i][j + 1] == ' ')
				map->cieling_tmp = ft_strdup(map->map[i] + j);
			j++;
		}
		i++;
	}
	printf("floor color is: %s\n", map->floor_tmp);
	printf("cieling color is: %s\n", map->cieling_tmp);
	
	if (!check_rgb(map))
		return (0);
	return (1);
}

int maps(t_cub *map)
{
    int i = 0;
    int start_index = 0;

    while (map->map[i] && map->map[i + 1])
    {
        if (map->map[i][0] == '1' && map->map[i + 1][0] == '1')
        {
            start_index = i;
            break;
        }
        i++;
    }
    map->dup_map = malloc(sizeof(char *) * (map->y - start_index + 1));
	i = 0;
	while (map->map[start_index + i] && map->map[start_index + i][0] != '\0')
	{
		map->dup_map[i] = ft_strdup(map->map[start_index + i]);
		i++;
	}
    map->dup_map[i] = NULL;
	if (!check_map(map, map->y))
		return (0);
    return (1);
}

static int	check_map_helper(t_cub *map, int len, t_var *v)
{
	while (map->dup_map[v->i] != NULL)
	{
		// if (ft_strlen(map->dup_map[v->i]) != ft_strlen(map->dup_map[0]))
		// 	return (ft_putendl_fd("Error: Map is not a rectangle", 2), 0);
		if (map->dup_map[v->i][0] != '1'
			|| map->dup_map[v->i][ft_strlen(map->dup_map[v->i]) - 1] != '1')
			return (ft_putendl_fd("Error: not surrounded by walls", 2), 0);
		else if (v->i == 0 || v->i == len - 1)
		{
			v->j = 0;
			while (map->dup_map[v->i][v->j])
			{
				if (map->dup_map[v->i][v->j] != '1')
					return (ft_putendl_fd("Error1", 2), 0);
				v->j++;
			}
		}
		v->i++;
	}
	return (1);
}

static int	check_map_helper2(t_cub *map_line, t_var *v)
{
	while (map_line->dup_map[v->i] != NULL)
	{
		v->j = 0;
		while (map_line->dup_map[v->i][v->j])
		{
			if ((map_line->dup_map[v->i][v->j] == 'N') || (map_line->dup_map[v->i][v->j] == 'S')
				|| (map_line->dup_map[v->i][v->j] == 'W') || (map_line->dup_map[v->i][v->j] == 'E')) 
			{
				map_line->dir = map_line->map[v->i][v->j];
				map_line->py = v->i;
				map_line->px = v->j;
				v->p++;
			}
			else if (map_line->dup_map[v->i][v->j] != '1'
				&& map_line->dup_map[v->i][v->j] != '0')
				return (ft_putendl_fd("Error: invalid characters", 2), 0);
			v->j++;
		}
		v->i++;
	}
	return (1);
}

int	check_map(t_cub *map_line, int map_len)
{
	t_var	v;

	v.i = 0;
	if (!check_map_helper(map_line, map_len, &v))
		return (0);
	v.i = 0;
	v.p = 0;
	if (!check_map_helper2(map_line, &v))
		return (0);
	if (v.p != 1)
		return (ft_putendl_fd("Error", 2), 0);
	return (1);
}

void	free_strings(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	check_file(char *file)
{
    int	i;

    i = 0;
    while (file[i])
        i++;
    if (file[i - 1] == 'b' && file[i - 2] == 'u' && file[i - 3] == 'c'
        && file[i - 4] == '.' && file[i] == '\0')
        return (1);
    return (0);
}
