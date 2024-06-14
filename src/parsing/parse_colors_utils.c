/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:00:32 by lmattern          #+#    #+#             */
/*   Updated: 2024/06/14 09:57:17 by lmattern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
this function initializes the color map with the color prefix and the right 
color pointer. It's used to parse the colors from the .cub file and assign them
to the right pointer quickly.
*/
void	init_color_map(t_color_map *color_map, t_cub *cub)
{
	color_map[0] = (t_color_map){"F ", &cub->styles.floor};
	color_map[1] = (t_color_map){"C ", &cub->styles.ceiling};
	color_map[2] = (t_color_map){NULL, NULL};
}

/*
this function extracts the color values from the line and returns them as a
string.
*/
int	check_color_input(char *color)
{
	size_t	len;

	len = 0;
	while (ft_isspace(*color))
		color++;
	while (ft_isdigit(*color))
	{
		color++;
		len++;
	}
	while (ft_isspace(*color))
		color++;
	if (*color || len == 0 || len > 3)
		return (ERROR);
	return (SUCCESS);
}

/*
this function checks if the color string format (',') is valid.
*/
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

/*
this function checks if the rgb color range value are valid.
*/
int	validate_rgb_range(int *value, const char *str)
{
	*value = ft_atoi(str);
	return (*value >= 0 && *value <= 255);
}
