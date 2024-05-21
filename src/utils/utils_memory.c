/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:00:32 by lmattern          #+#    #+#             */
/*   Updated: 2024/05/20 16:52:36 by lmattern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	print_map(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			ft_printf("%c", map->grid[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

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

int	clean_return(char *line, char **lines, int status)
{
	ft_free(line);
	get_next_line(-1);
	ft_free_double_array(lines);
	return (status);
}
