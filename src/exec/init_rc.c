/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:05:21 by fprevot           #+#    #+#             */
/*   Updated: 2024/05/21 16:35:28 by lmattern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
this function load the texture from the path and stores it in the texture 
creatingthe mlx image and getting the data address.
*/
void	load_texture(t_ray *rc, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(rc->mlx, path, \
	&texture->width, &texture->height);
	if (!texture->img)
		exit(EXIT_FAILURE);
	// question marks ????
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_ppixel, \
	&texture->line_len, &texture->endian);
}

/*
this function loads the textures from the cub data structure and stores them in
the raycasting structure.
*/
void	load_textures(t_ray *rc, t_textures textures)
{
	load_texture(rc, &rc->texture[0], textures.we);
	load_texture(rc, &rc->texture[1], textures.ea);
	load_texture(rc, &rc->texture[2], textures.no);
	load_texture(rc, &rc->texture[3], textures.so);
}

void	init_player_dir(t_cub *cub, t_ray *rc)
{
	if (cub->player.heading == 'N')
	{
		rc->dir_y = -1.01;
		rc->plane_x = 0.66;
	}
	else if (cub->player.heading == 'S')
	{
		rc->dir_y = 1.01;
		rc->plane_x = -0.66;
		rc->plane_y = 0.0;
	}
	else if (cub->player.heading == 'E')
	{
		rc->dir_x = 1.01;
		rc->plane_y = 0.66;
	}
	else if (cub->player.heading == 'W')
	{
		rc->dir_x = -1.01;
		rc->plane_y = -0.66;
	}
}

/*
this function initializes the raycasting structure according to the cub data
structure and returns the raycasting structure.
*/
t_ray	*init_raycasting(t_cub *cub)
{
	t_ray	*rc;

	rc = ft_calloc(1, sizeof(t_ray));
	rc->mlx = mlx_init();
	// protect init
	rc->win_width = 1600;
	rc->win_height = 1200;
	rc->win = mlx_new_window(rc->mlx, rc->win_width, rc->win_height, "Cub3D");
	// protect new_window
	rc->pos_x = (double)cub->player.x + 0.5;
	rc->pos_y = (double)cub->player.y + 0.5;
	init_player_dir(cub, rc);
	rc->map = &cub->map;
	rc->floor_color = cub->styles.floor;
	rc->ceiling_color = cub->styles.ceiling;
	load_textures(rc, cub->textures);
	return (rc);
}
