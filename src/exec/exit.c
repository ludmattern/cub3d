/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:02:07 by fprevot           #+#    #+#             */
/*   Updated: 2024/05/20 17:22:08 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	free_textures(t_ray *rc, int i)
{
	while (i < 4)
	{
		if (rc->texture[i].img)
			mlx_destroy_image(rc->mlx, rc->texture[i].img);
		i++;
	}
}

void free_mlx(t_ray *rc)
{
	//free_textures(rc, 0);
	if (rc->win)
		mlx_destroy_window(rc->mlx, rc->win);
	if (rc->mlx)
		mlx_destroy_display(rc->mlx);
	if (rc->mlx)
		free(rc->mlx);
}

void free_all(t_ray *rc)
{
	free_mlx(rc);
	free(rc);
}
