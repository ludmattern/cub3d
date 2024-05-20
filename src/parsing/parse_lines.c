/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:01:31 by lmattern          #+#    #+#             */
/*   Updated: 2024/05/20 15:38:55 by lmattern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	store_player_position(t_cub *cub, size_t i, size_t j, char heading)
{
	cub->player.x = j;
	cub->player.y = i;
	cub->player.heading = heading;
	cub->map.grid[i][j] = '0';
}

static void	store_grid_cell_value(t_cub *cub, size_t i, size_t j, char **lines)
{
	if (j < ft_strlen(lines[i]))
	{
		if (lines[i][j] == 'N'
			|| lines[i][j] == 'S'
			|| lines[i][j] == 'E'
			|| lines[i][j] == 'W')
			store_player_position(cub, i, j, lines[i][j]);
		else if (lines[i][j] == '\n')
			cub->map.grid[i][j] = ' ';
		else
			cub->map.grid[i][j] = lines[i][j];
	}
	else
		cub->map.grid[i][j] = ' ';
}

size_t	find_longest_line(char **lines)
{
	size_t	i;
	size_t	j;
	size_t	max;

	i = 0;
	max = 0;
	while (lines[i])
	{
		j = ft_strlen(lines[i]);
		if (lines[i][j - 1] == '\n')
			j--;
		while (j > 0 && lines[i][j - 1] == ' ')
			j--;
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}

int	parse_lines(t_cub *cub, char **lines)
{
	size_t	i;
	size_t	j;

	cub->map.width = find_longest_line(lines);
	cub->map.grid = ft_calloc(cub->map.height, sizeof(int *));
	if (!cub->map.grid)
		return (ft_eprintf(ERR ALLOC_ERR" for map\n"), ERROR);
	i = -1;
	while (++i < cub->map.height)
	{
		cub->map.grid[i] = ft_calloc(cub->map.width, sizeof(int));
		if (!cub->map.grid[i])
			return (ft_free_double_int_array(cub->map.grid, i), \
			ft_eprintf(ERR ALLOC_ERR" for map\n"), ERROR);
		j = -1;
		while (++j < cub->map.width)
			store_grid_cell_value(cub, i, j, lines);
	}
	return (SUCCESS);
}
