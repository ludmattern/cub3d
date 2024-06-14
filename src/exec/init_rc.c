/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:05:21 by fprevot           #+#    #+#             */
/*   Updated: 2024/06/14 11:33:23 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
this function load the texture from the path and stores it in the texture 
creatingthe mlx image and getting the data address.
*/
int	load_texture(t_ray *rc, t_texture *texture, char *path)
{
	int	i;

	i = 0;
	texture->img = mlx_xpm_file_to_image(rc->mlx, path, &texture->width, \
		&texture->height);
	if (!texture->img)
	{
		while (i < 4)
		{
			if (rc->texture[i].img != NULL)
				mlx_destroy_image(rc->mlx, rc->texture[i].img);
			i++;
		}
		return (2);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_ppixel, \
		&texture->line_len, &texture->endian);
	return (0);
}

/*
this function loads the textures from the cub data structure and stores them in
the raycasting structure.
*/
int	load_textures(t_ray *rc, t_textures textures)
{
	int	err;

	err = load_texture(rc, &rc->texture[0], textures.we);
	if (err == 2)
		return (2);
	err = load_texture(rc, &rc->texture[1], textures.ea);
	if (err == 2)
		return (2);
	err = load_texture(rc, &rc->texture[2], textures.no);
	if (err == 2)
		return (2);
	err = load_texture(rc, &rc->texture[3], textures.so);
	if (err == 2)
		return (2);
	return (0);
}

void	init_player_dir(t_cub *cub, t_ray *rc)
{
	rc->pos_x = (double)cub->player.x + 0.5;
	rc->pos_y = (double)cub->player.y + 0.5;
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

void	free_err(t_ray *rc)
{
	if (rc->win)
		mlx_destroy_window(rc->mlx, rc->win);
	if (rc->mlx)
		mlx_destroy_display(rc->mlx);
	if (rc->mlx)
		ft_free(rc->mlx);
	free(rc);
}

t_ray	*init_raycasting(t_cub *cub)
{
	t_ray	*rc;

	rc = ft_calloc(1, sizeof(t_ray));
	if (!rc)
		return (NULL);
	rc->cub = cub;
	rc->mlx = mlx_init();
	if (!rc->mlx)
		return (free(rc), NULL);
	rc->win_width = 1600;
	rc->win_height = 1200;
	rc->win = mlx_new_window(rc->mlx, rc->win_width, rc->win_height, "Cub3D");
	if (!rc->win)
		return (mlx_destroy_display(rc->mlx), free(rc->mlx), free(rc), NULL);
	init_player_dir(cub, rc);
	rc->map = &cub->map;
	rc->floor_color = cub->styles.floor;
	rc->ceiling_color = cub->styles.ceiling;
	if (load_textures(rc, cub->textures) == 2)
		return (free_err(rc), NULL);
	return (rc);
}
