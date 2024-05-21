/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_wall_dim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:03:18 by fprevot           #+#    #+#             */
/*   Updated: 2024/05/21 12:41:39 by lmattern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
this function calculates the distance between the player and the wall hit by 
the ray.
*/
void	calc_wall_distance(t_scene_ctx *ctx, t_ray *rc)
{
	if (ctx->side == 0)
		ctx->wall_dist = (ctx->map_x - rc->pos_x + (1 - ctx->step_x) / 2)
			/ ctx->ray_dir_x;
	else
		ctx->wall_dist = (ctx->map_y - rc->pos_y + (1 - ctx->step_y) / 2)
			/ ctx->ray_dir_y;
	ctx->line_height = (int)(rc->win_height / ctx->wall_dist);
}

/*
this function calculates the positions where the wall will be drawn.
*/
void	calc_draw_positions(t_scene_ctx *ctx, t_ray *rc)
{
	ctx->draw_start = -ctx->line_height / 2 + rc->win_height / 2;
	if (ctx->draw_start < 0)
		ctx->draw_start = 0;
	ctx->draw_end = ctx->line_height / 2 + rc->win_height / 2;
	if (ctx->draw_end >= rc->win_height)
		ctx->draw_end = rc->win_height - 1;
}

/*
this function calculates the exact position where the ray hit the wall needed
for texture.
*/
void	calc_wall_hit_position(t_scene_ctx *ctx, t_ray *rc)
{
	if (ctx->side == 0)
		ctx->wall_x = rc->pos_y + ctx->wall_dist * ctx->ray_dir_y;
	else
		ctx->wall_x = rc->pos_x + ctx->wall_dist * ctx->ray_dir_x;
	ctx->wall_x -= floor(ctx->wall_x);
}

/*
this function calculates the x position in the texture.
*/
void	calc_texture_x(t_scene_ctx *ctx, t_ray *rc)
{
	ctx->text_x = (int)(ctx->wall_x * (double)rc->texture[ctx->text_num].width);
	if (ctx->side == 0 && ctx->ray_dir_x > 0)
		ctx->text_x = rc->texture[ctx->text_num].width - ctx->text_x - 1;
	if (ctx->side == 1 && ctx->ray_dir_y < 0)
		ctx->text_x = rc->texture[ctx->text_num].width - ctx->text_x - 1;
}

/*
this function calculates the dimensions, position and color of the wall to draw.
*/
void	calc_wall_dimensions(t_scene_ctx *ctx, t_ray *rc)
{
	calc_wall_distance(ctx, rc);
	calc_draw_positions(ctx, rc);
	calc_wall_hit_position(ctx, rc);
	calc_texture_x(ctx, rc);
}
