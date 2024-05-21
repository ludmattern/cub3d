/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:00:32 by lmattern          #+#    #+#             */
/*   Updated: 2024/05/21 17:05:42 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
this function frees the memory allocated for the textures and the cub data 
structure. It's meant to be called during the parsing process.
*/
int	clean_exit(t_cub *cub, int exit_code)
{
	ft_close(cub->filefd);
	ft_free(cub->textures.no);
	ft_free(cub->textures.so);
	ft_free(cub->textures.we);
	ft_free(cub->textures.ea);
	ft_free(cub);
	return (exit_code);
}

/*
this function frees the memory allocated for the line and the lines array.
It's meant to be called during the parsing process.
*/
int	clean_return(char *line, char **lines, int status)
{
	ft_free(line);
	get_next_line(-1);
	ft_free_double_array(lines);
	return (status);
}

int	handle_img_err(t_ray *rc)
{
	ft_free_double_int_array(rc->cub->map.grid, rc->cub->map.height);
	free(rc->cub->textures.ea);
	free(rc->cub->textures.no);
	free(rc->cub->textures.so);
	free(rc->cub->textures.we);
	free(rc->cub);
	free_all(rc);
	return (EXIT_FAILURE);
}
