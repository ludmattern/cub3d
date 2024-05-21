/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:03:13 by fprevot           #+#    #+#             */
/*   Updated: 2024/05/21 11:50:30 by lmattern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
this function initializes the context structure with the values needed to draw
the scene.
*/
void	ctx_scene_init(t_scene_ctx *ctx, t_ray *rc, int x)
{
	ctx->camera_x = 2 * x / (double)rc->win_width - 1; // direction de la cam
	ctx->ray_dir_x = rc->dir_x + rc->plane_x * ctx->camera_x; // direction x du rayon 
	ctx->ray_dir_y = rc->dir_y + rc->plane_y * ctx->camera_x; // direction y du rayon
	ctx->map_x = (int)rc->pos_x; // position du joueur dans la map
	ctx->map_y = (int)rc->pos_y; // position du joueur dans la map
	ctx->delta_dist_x = fabs(1 / ctx->ray_dir_x); // ligne la plus proche en x
	ctx->delta_dist_y = fabs(1 / ctx->ray_dir_y); // ligne la plus proche en y
	ctx->hit = 0;
	ctx->ceiling_color = rc->ceiling_color;
	ctx->floor_color = rc->floor_color;
	ctx->texture_num = 0;
	ctx->wall_x = 0;
	ctx->texture_x = 0;
	ctx->texture_y = 0;
}

/*
this function changes the pixel color in the image.
*/
void	pixel_put_to_img(t_data_img *data, int x, int y, int color)
{
	char	*pix_in_grid;
	
	pix_in_grid = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)pix_in_grid = color;
}

/*
this function calculates the dimensions, position and color of the wall to draw 
then draws it.
*/
void	draw_tex(t_scene_ctx *ctx, t_ray *rc, int x, t_data_img *img)
{
	t_texture	*tex;
	double		step;
	double		tex_pos;
	int			y;
	int			color;

	tex = &rc->texture[ctx->texture_num];
	step = 1.0 * tex->height / ctx->line_height;
	tex_pos = (ctx->draw_start - rc->win_height / 2 + ctx->line_height / 2) * step;
	y = ctx->draw_start;
	while (y++ < ctx->draw_end)
	{
		ctx->texture_y = (int)tex_pos % tex->height;  // Calc la coordonnee y
		tex_pos += step;  // avance dans la texture
		color = *(int *)(tex->addr + (ctx->texture_y * \
		tex->line_length + ctx->texture_x * (tex->bits_per_pixel / 8))); // recup la couleur du pixel dans la texture
		pixel_put_to_img(img, x, y, color);
	}
}

/*
this function draws all the line from the top to the bottom of the screen.
*/
void	draw_line(t_scene_ctx *ctx, t_ray *rc, int x, t_data_img *img)
{
	int	y;
	
	draw_tex(ctx, rc, x, img);
	y = 0;
	while (y++ < ctx->draw_start)
		pixel_put_to_img(img, x, y, ctx->ceiling_color);
	y = ctx->draw_end;
	while (y++ < rc->win_height)
		pixel_put_to_img(img, x, y, ctx->floor_color);
}

/*
this function calculates the right heading of the ray and the distance to the 
next horizontal and vertical line.
*/
void	ray_dir(t_scene_ctx *ctx, t_ray *rc) //savoir dans quelle dir lance le ray te la dist avec la prochaine ligne //initialisation du rayon
{
	if (ctx->ray_dir_x < 0)
	{
		ctx->step_x = -1;
		ctx->side_dist_x = (rc->pos_x - ctx->map_x) * ctx->delta_dist_x; //DIstance entre le debut du ray et la prochaune pos en x ou y
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
		if (ctx->side_dist_x < ctx->side_dist_y) //chekc si le next murs est hori ou pos
		{
			ctx->side_dist_x += ctx->delta_dist_x;
			ctx->map_x += ctx->step_x;
			ctx->side = 0; // le mur touché est vertical
		}
		else
		{
			ctx->side_dist_y += ctx->delta_dist_y;
			ctx->map_y += ctx->step_y;
			ctx->side = 1; // le mur touché est horizontal
		}
		if (rc->map->grid[ctx->map_y][ctx->map_x] > 48) // stop si murs
		{
			ctx->hit = 1; //MUrs touche
			ctx->texture_num = get_tex_num(ctx); // get la texture du murs
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
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
	&img.line_length, &img.endian);
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
