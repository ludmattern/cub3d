/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:03:07 by fprevot           #+#    #+#             */
/*   Updated: 2024/05/21 11:18:27 by lmattern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
this function handles the keypress event received by the mlx loop and updates 
the raycasting structure accordingly.
*/
int	handle_keypress(int keycode, t_ray *rc)
{
	if (keycode == 65307)
	{
		free_all(rc);
		exit(0);
	}
	if (keycode == 119)
		rc->move_forward = 1;
	if (keycode == 115)
		rc->move_backward = 1;
	if (keycode == 100)
		rc->move_right = 1;
	if (keycode == 97)
		rc->move_left = 1;
	if (keycode == 65361)
		rc->cam_left = 1;
	if (keycode == 65363)
		rc->cam_right = 1;
	return (0);
}

/*
this function handles the keyrelease event received by the mlx loop and updates
the raycasting structure accordingly.
*/
int	handle_keyrelease(int keycode, t_ray *rc)
{
	if (keycode == 119)
		rc->move_forward = 0;
	if (keycode == 115)
		rc->move_backward = 0;
	if (keycode == 100)
		rc->move_right = 0;
	if (keycode == 97)
		rc->move_left = 0;
	if (keycode == 65361)
		rc->cam_left = 0;
	if (keycode == 65363)
		rc->cam_right = 0;
	return (0);
}

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
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, \
	&texture->line_length, &texture->endian);
}

/*
this function loads the textures from the cub data structure and stores them in
the raycasting structure.
*/
void	load_textures(t_ray *rc, t_textures textures)
{
	load_texture(rc, &rc->texture[0], textures.no);
	load_texture(rc, &rc->texture[1], textures.so);
	load_texture(rc, &rc->texture[2], textures.ea);
	load_texture(rc, &rc->texture[3], textures.we);
}

/*
this function initializes the raycasting structure according to the cub data
structure and returns the raycasting structure.
*/
t_ray	*init_raycasting(t_cub *cub)
{
	t_ray	*rc;

	rc = malloc(sizeof(t_ray));
	rc->mlx = mlx_init();
	rc->win_width = 1600;
	rc->win_height = 1200;
	rc->win = mlx_new_window(rc->mlx, rc->win_width, rc->win_height, "Cub3D");
	rc->pos_x = (double)cub->player.x + 0.1;
	rc->pos_y = (double)cub->player.y + 0.1;
	rc->dir_x = -1;// a changer selon la dir (N,W,S,E) du j au debut
	rc->dir_y = 0;// a changer selon la dir (N,W,S,E) du j au debut
	rc->plane_x = 0;// le FOV
	rc->plane_y = 0.66; // le FOV
	rc->map = &cub->map;
	rc->move_left = 0;
	rc->move_right = 0;
	rc->move_forward = 0;
	rc->move_backward = 0;
	rc->cam_left = 0;
	rc->cam_right = 0;
	load_textures(rc, cub->textures);
	return (rc);
}

/*
this function starts the game loop and handles the keypress and keyrelease 
events.
*/
void	start_exec(t_cub *cub)
{
	t_ray	*rc;

	rc = init_raycasting(cub);
	mlx_hook(rc->win, 2, 1L << 0, handle_keypress, rc);
	mlx_hook(rc->win, 3, 1L << 1, handle_keyrelease, rc);
	mlx_loop_hook(rc->mlx, (int (*)(void *))update_frame, rc);
	mlx_loop(rc->mlx);
}
