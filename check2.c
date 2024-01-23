#include "cub3d.h"

 //this fucntion needs mlx so we can skip it for now and continue with the parsing part
 //now we have to check for map and store the map after checking
 //we have to check for the players direction and store it so we can print it using mlx
 
static int check_texture_file(char *path)
{
    int fd;
    if ((fd = open(path, O_RDONLY)) < 0)
        return (0);
    return (1);
}

int store_textures(t_cub *map)
{
    // printf("texture path is: %s\n", map->no_tmp);
    // printf("texture path is: %s\n", map->so_tmp);
    // printf("texture path is: %s\n", map->we_tmp);
    // printf("texture path is: %s\n", map->ea_tmp);

    map->path = malloc(sizeof(t_path));
    if (!map->no_tmp || !map->so_tmp || !map->ea_tmp || !map->we_tmp)
        return (printf("Error: Missing Texture\n"), 0);
    if (!map->path)
        return (printf("Error: Malloc failed\n"), 0);
    // Check if textures are valid xpm files
    if (!check_texture_file(map->no_tmp))
        return (printf("Error: Invalid north texture file\n"), 0);
    if (!check_texture_file(map->so_tmp))
        return (printf("Error: Invalid south texture file\n"), 0);
    if (!check_texture_file(map->ea_tmp))
        return (printf("Error: Invalid east texture file\n"), 0);
    if (!check_texture_file(map->we_tmp))
        return (printf("Error: Invalid west texture file\n"), 0);

    // Initialize path to textures
    map->texture[0] = ft_strdup(map->no_tmp);
    map->texture[1] = ft_strdup(map->so_tmp);
    map->texture[2] = ft_strdup(map->ea_tmp);
    map->texture[3] = ft_strdup(map->we_tmp);
    map->texture[4] = NULL;
    free(map->no_tmp);
    free(map->so_tmp);
    free(map->ea_tmp);
    free(map->we_tmp);

    // for(int i = 0; map->texture[i]; i++)
    //     printf("%s\n", map->texture[i]);


    return (1);
}

int check_rgb(t_cub *map)
{
    int i = 0;
    int j = 0;
    int count = 0;

    while (map->floor_tmp[i])
    {
        if (map->floor_tmp[i] == ',')
            count++;
        i++;
    }
    if (count != 2)
        return (printf("Error: Wrong Color\n"), 0);
    count = 0;
    while (map->cieling_tmp[j])
    {
        if (map->cieling_tmp[j] == ',')
            count++;
        j++;
    }
    if (count != 2)
        return (printf("Error: Wrong Color\n"), 0);

    map->cieling = (int *)malloc(sizeof(int) * 3);
    map->floor = (int *)malloc(sizeof(int) * 3);
    if (!store_rgb(map))
        return (0);
    return (1);
}

int store_rgb(t_cub *map)
{
    int i = 0;
    int j = 0;
    int len = 0;
    int flag = 0;

    printf("floor tmp is : %s\n", map->floor_tmp);
    printf("cieling tmp is : %s\n", map->cieling_tmp);
    while (map->floor_tmp[i])
    {
        if (map->floor_tmp[i] == ',')
            flag++;
        if (flag == 0)
            len++;
        i++;
    }
    map->cfloor = malloc(sizeof(char) * (len + 1));
    map->ccieling = malloc(sizeof(char) * (len + 1));
    ft_strlcpy(map->cfloor, map->floor_tmp, len + 1);
    ft_strlcpy(map->ccieling, map->cieling_tmp, len + 1);
    flag = 0;
    len = 0;
    while (map->cieling_tmp[j])
    {
        if (map->cieling_tmp[j] == ',')
            flag++;
        if (flag == 0)
            len++;
        j++;
    }
    // printf("cieling tmp is : %s\n", map->cieling_tmp);
    // map->cieling[0] = ft_atoi(map->cieling_tmp);
    // map->cieling[1] = ft_atoi(map->cieling_tmp + len + 1);
    // map->cieling[2] = ft_atoi(map->cieling_tmp + len + 1 + len + 1);

    // if (map->floor[0] < 0 || map->floor[0] > 255 || map->floor[1] < 0 || map->floor[1] > 255 || map->floor[2] < 0 || map->floor[2] > 255)
    //     return (printf("Error: Wrong Color\n"), 0);
    // printf("floor = %d, %d, %d\n", map->floor[0], map->floor[1], map->floor[2]);
    // printf("cieling = %d, %d, %d\n", map->cieling[0], map->cieling[1], map->cieling[2]);
    
    // map->cfloor = store_rgb_string(map->floor[0], map->floor[1], map->floor[2]);
    // map->ccieling = store_rgb_string(map->cieling[0], map->cieling[1], map->cieling[2]);
    // printf("cfloor = %s\n", map->cfloor);
    // printf("ccieling = %s\n", map->ccieling);
    // printf("cfloor = %s\n", map->cfloor);
    // printf("ccieling = %s\n", map->ccieling);
    return (1);
}


int store_map(t_cub *map)
{
    t_var v;
    v.i = 0;
    v.j = 0;

    // Allocate memory for xmap
    map->xmap = malloc(sizeof(char *) * (map->y + 1));
    if (!map->xmap)
        return (printf("Error: Malloc failed\n"), 0);

    while (map->dup_map[v.i] != NULL)
    {
        v.j = 0;
        int row_len = strlen(map->dup_map[v.i]);
        map->xmap[v.i] = malloc(sizeof(char) * (row_len + 1)); // Allocate memory for each row
        if (!map->xmap[v.i])
            return (printf("Error: Malloc failed\n"), 0);
        while (map->dup_map[v.i][v.j])
        {
            map->xmap[v.i][v.j] = map->dup_map[v.i][v.j];
            v.j++;
        }
        map->xmap[v.i][v.j] = '\0'; // Null-terminate the row
        v.i++;
    }
    map->xmap[v.i] = NULL;
    // print_map(map);
    return (1);
}

void print_map(t_cub *map)
{
    int i = 0;

    while (map->xmap[i])
    {
        printf("%s\n", map->xmap[i]);
        i++;
    }
}

char *store_rgb_string(int r, int g, int b)
{
    char *r_str = ft_itoa(r);
    char *g_str = ft_itoa(g);
    char *b_str = ft_itoa(b);

    char *rgb_string = malloc(strlen(r_str) + strlen(g_str) + strlen(b_str) + 3); // +3 for two commas and a null terminator

    strcpy(rgb_string, r_str);
    strcat(rgb_string, ",");
    strcat(rgb_string, g_str);
    strcat(rgb_string, ",");
    strcat(rgb_string, b_str);

    free(r_str);
    free(g_str);
    free(b_str);

    return rgb_string;
}