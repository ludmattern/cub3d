/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:00:32 by lmattern          #+#    #+#             */
/*   Updated: 2024/05/19 13:05:44 by lmattern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	init_color_map(t_color_map *color_map, t_cub *cub)
{
	color_map[0] = (t_color_map){"F ", &cub->styles.floor};
	color_map[1] = (t_color_map){"C ", &cub->styles.ceiling};
	color_map[2] = (t_color_map){NULL, NULL};
}

int	check_color_input(char *color)
{
	while (ft_isspace(*color))
		color++;
	while (ft_isdigit(*color))
		color++;
	while (ft_isspace(*color))
		color++;
	if (*color)
		return (ERROR);
	return (SUCCESS);
}

int	check_comma(char *str, const char *line)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == ',')
			count++;
		str++;
	}
	if (count > 2)
		return (ft_eprintf(ERR"Invalid color format : %s", line), ERROR);
	return (SUCCESS);
}

int	validate_rgb_range(int *value, const char *str)
{
	*value = ft_atoi(str);
	return (*value >= 0 && *value <= 255);
}
