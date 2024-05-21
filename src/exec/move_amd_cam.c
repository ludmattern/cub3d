/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_amd_cam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:03:24 by fprevot           #+#    #+#             */
/*   Updated: 2024/05/21 11:30:52 by lmattern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
th function moves the player forward or backward depending on the key pressed.
*/
void	move_forward_backward(t_ray *rc, double ms)
{
	if (rc->move_forward)
	{
		if (rc->map->grid[(int)(rc->pos_y)][(int)(rc->pos_x + rc->dir_x * ms)]
			== 48)
			rc->pos_x += rc->dir_x * ms;
		if (rc->map->grid[(int)(rc->pos_y + rc->dir_y * ms)][(int)(rc->pos_x)]
			== 48)
			rc->pos_y += rc->dir_y * ms;
	}
	if (rc->move_backward)
	{
		if (rc->map->grid[(int)(rc->pos_y)][(int)(rc->pos_x - rc->dir_x * ms)]
			== 48)
			rc->pos_x -= rc->dir_x * ms;
		if (rc->map->grid[(int)(rc->pos_y - rc->dir_y * ms)][(int)(rc->pos_x)]
			== 48)
			rc->pos_y -= rc->dir_y * ms;
	}
}

/*
this function moves the player left or right depending on the key pressed.
*/
void	move_left_right(t_ray *rc, double ms)
{
	if (rc->move_right)
	{
		if (rc->map->grid[(int)(rc->pos_y)][(int)(rc->pos_x + rc->plane_x * ms)]
			== 48)
			rc->pos_x += rc->plane_x * ms;
		if (rc->map->grid[(int)(rc->pos_y + rc->plane_y * ms)][(int)(rc->pos_x)]
			== 48)
			rc->pos_y += rc->plane_y * ms;
	}
	if (rc->move_left)
	{
		if (rc->map->grid[(int)(rc->pos_y)][(int)(rc->pos_x - rc->plane_x * ms)]
			== 48)
			rc->pos_x -= rc->plane_x * ms;
		if (rc->map->grid[(int)(rc->pos_y - rc->plane_y * ms)][(int)(rc->pos_x)]
			== 48)
			rc->pos_y -= rc->plane_y * ms;
	}
}

/*
this function rotates the camera left or right depending on the key pressed.
*/
void	rotate_camera(t_ray *rc, double ms)
{
	double	old_dir_x;
	double	old_plane_x;

	if (rc->cam_right)
	{
		old_dir_x = rc->dir_x;
		rc->dir_x = rc->dir_x * cos(-ms) - rc->dir_y * sin(-ms);
		rc->dir_y = old_dir_x * sin(-ms) + rc->dir_y * cos(-ms);
		old_plane_x = rc->plane_x;
		rc->plane_x = rc->plane_x * cos(-ms) - rc->plane_y * sin(-ms);
		rc->plane_y = old_plane_x * sin(-ms) + rc->plane_y * cos(-ms);
	}
	if (rc->cam_left)
	{
		old_dir_x = rc->dir_x;
		rc->dir_x = rc->dir_x * cos(ms) - rc->dir_y * sin(ms);
		rc->dir_y = old_dir_x * sin(ms) + rc->dir_y * cos(ms);
		old_plane_x = rc->plane_x;
		rc->plane_x = rc->plane_x * cos(ms) - rc->plane_y * sin(ms);
		rc->plane_y = old_plane_x * sin(ms) + rc->plane_y * cos(ms);
	}
}

/*
this function updates the frame of the game when the player moves or rotates the
camera.
*/
int	update_frame(t_ray *rc, t_cub *cub)
{
	double	ms;

	ms = 0.1;
	move_forward_backward(rc, ms);
	move_left_right(rc, ms);
	rotate_camera(rc, ms);
	draw_scene(rc, 0, cub);
	return (0);
}
