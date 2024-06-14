/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:02:42 by fprevot           #+#    #+#             */
/*   Updated: 2024/06/14 17:52:04 by lmattern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
this function changes the pixel color in the image.
*/
void	pixel_put_to_img(t_data_img *data, int x, int y, int color)
{
	char	*pix_in_grid;

	pix_in_grid = data->addr + (y * data->line_len + x \
	* (data->bits_ppixel / 8));
	*(unsigned int *)pix_in_grid = color;
}

/*
this function calculates the dimensions, position and color of the wall to draw 
then draws it.
*/
void    draw_tex(t_scene_ctx *ctx, t_ray *rc, int x, t_data_img *img)
{
    t_texture    *tex;
    double        step;
    double        tex_pos;
    int            y;
    int            color;

    tex = &rc->texture[ctx->text_num];
    step = 1.0 * tex->height / ctx->line_height;
    tex_pos = (ctx->draw_start - rc->win_height / 2 + \
    ctx->line_height / 2) * step;
    y = ctx->draw_start;
    while (y++ < ctx->draw_end)
    {
        ctx->texture_y = (int)tex_pos % tex->height;
        tex_pos += step;
        color = *(int *)(tex->addr + (ctx->texture_y * tex->line_len + \
        (tex->width - 1 - ctx->text_x) * (tex->bits_ppixel / 8)));
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
