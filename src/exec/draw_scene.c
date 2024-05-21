/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:03:13 by fprevot           #+#    #+#             */
/*   Updated: 2024/05/21 14:53:01 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
this function initializes the context structure with the values needed to draw
the scene.
*/
void	ctx_scene_init(t_scene_ctx *ctx, t_ray *rc, int x)
{
	ctx->camera_x = 2 * x / (double)rc->win_width - 1;
	ctx->ray_dir_x = rc->dir_x + rc->plane_x * ctx->camera_x;
	ctx->ray_dir_y = rc->dir_y + rc->plane_y * ctx->camera_x;
	ctx->map_x = (int)rc->pos_x;
	ctx->map_y = (int)rc->pos_y;
	ctx->delta_dist_x = fabs(1 / ctx->ray_dir_x);
	ctx->delta_dist_y = fabs(1 / ctx->ray_dir_y);
	ctx->hit = 0;
	ctx->ceiling_color = rc->ceiling_color;
	ctx->floor_color = rc->floor_color;
	ctx->text_num = 0;
	ctx->wall_x = 0;
	ctx->text_x = 0;
	ctx->texture_y = 0;
}

/*
this function calculates the right heading of the ray and the distance to the 
next horizontal and vertical line.
*/
void	ray_dir(t_scene_ctx *ctx, t_ray *rc)
{
	if (ctx->ray_dir_x < 0)
	{
		ctx->step_x = -1;
		ctx->side_dist_x = (rc->pos_x - ctx->map_x) * ctx->delta_dist_x;
	}
	else
	{
		ctx->step_x = 1;
		ctx->side_dist_x = (ctx->map_x + 1.0 - rc->pos_x) * ctx->delta_dist_x;
	}
	if (ctx->ray_dir_y < 0)
	{
		ctx->step_y = -1;
		ctx->side_dist_y = (rc->pos_y - ctx->map_y) * ctx->delta_dist_y;
	}
	else
	{
		ctx->step_y = 1;
		ctx->side_dist_y = (ctx->map_y + 1.0 - rc->pos_y) * ctx->delta_dist_y;
	}
}

/*
this function returns the texture number according to the side of the wall hit.
*/
int	get_tex_num(t_scene_ctx *ctx)
{
	if (ctx->side == 0)
	{
		if (ctx->ray_dir_x < 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (ctx->ray_dir_y < 0)
			return (2);
		else
			return (3);
	}
}

/*
the function is the direct drawing distance algorithm. It calculates the distance
to the next wall and the side of the wall hit.
*/
void	dda(t_scene_ctx *ctx, t_ray *rc)
{
	while (ctx->hit == 0)
	{
		if (ctx->side_dist_x < ctx->side_dist_y)
		{
			ctx->side_dist_x += ctx->delta_dist_x;
			ctx->map_x += ctx->step_x;
			ctx->side = 0;
		}
		else
		{
			ctx->side_dist_y += ctx->delta_dist_y;
			ctx->map_y += ctx->step_y;
			ctx->side = 1;
		}
		if (rc->map->grid[ctx->map_y][ctx->map_x] > 48)
		{
			ctx->hit = 1;
			ctx->text_num = get_tex_num(ctx);
		}
	}
}

/*
this function draws the scene pixel by pixel on the x axis of the screen.
*/
void	draw_scene(t_ray *rc, int x)
{
	t_data_img	img;
	t_scene_ctx	ctx;

	img.img = mlx_new_image(rc->mlx, rc->win_width, rc->win_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_ppixel, \
	&img.line_len, &img.endian);
	img.width = rc->win_width;
	img.height = rc->win_height;
	while (x < rc->win_width)
	{
		ctx_scene_init(&ctx, rc, x);
		ray_dir(&ctx, rc);
		dda(&ctx, rc);
		calc_wall_dimensions(&ctx, rc);
		draw_line(&ctx, rc, x, &img);
		x++;
	}
	mlx_put_image_to_window(rc->mlx, rc->win, img.img, 0, 0);
	mlx_destroy_image(rc->mlx, img.img);
}
