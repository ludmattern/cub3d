/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:00:32 by lmattern          #+#    #+#             */
/*   Updated: 2024/05/21 12:52:35 by lmattern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
this function extracts the color values from the line and returns them as a 
string.
*/
static char	*extract_colors_string_values(const char *line, size_t len)
{
	size_t	i;

	i = 2;
	while (ft_isspace(line[i]))
		i++;
	if (line[len - 1] == '\n')
		return (ft_strndup(line + i, len - i - 1));
	else
		return (ft_strdup(line + i));
}

/*
this function checks if the color string is valid.
*/
static char	**split_and_check_color_string_format(char *str)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb)
		return (ft_eprintf(ERR ALLOC_ERR" for color\n"), free(str), NULL);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		ft_eprintf(ERR"Invalid color format : %s\n", str);
		return (ft_free_double_array(rgb), free(str), NULL);
	}
	return (free(str), rgb);
}

/*
this function checks if the rgb color range value are valid then stores them in
the color integer pointer as a 24 bits color.
*/
static int	parse_colors_to_struct(int *color, char **rgb)
{
	int	value;
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!check_color_input(rgb[i]) || !validate_rgb_range(&value, rgb[i]))
		{
			ft_eprintf(ERR"Invalid color value : %s\n", rgb[i]);
			return (ft_free_double_array(rgb), ERROR);
		}
		if (i == 0)
			*color = value << 16;
		else if (i == 1)
			*color |= value << 8;
		else if (i == 2)
			*color |= value;
		i++;
	}
	return (ft_free_double_array(rgb), SUCCESS);
}

/*
this function extracts the color values from the line, checks if the color is
valid and stores it in the cub data structure.
*/
static int	extract_and_parse_colors(int *color, const char *line)
{
	char	*tmp;
	char	**rgb;

	tmp = extract_colors_string_values(line, ft_strlen(line));
	if (!tmp)
		return (ft_eprintf(ERR ALLOC_ERR" for color\n"), ERROR);
	if (!check_comma(tmp, line))
		return (free(tmp), ERROR);
	rgb = split_and_check_color_string_format(tmp);
	if (!rgb)
		return (ERROR);
	if (!parse_colors_to_struct(color, rgb))
		return (ERROR);
	return (SUCCESS);
}

/*
this function processes the colors from the .cub file and assigns the color to 
the cub data structure.
*/
int	process_style(t_cub *cub, char *line)
{
	size_t			j;
	t_color_map		color_map[3];

	j = -1;
	init_color_map(color_map, cub);
	while (color_map[++j].prefix)
	{
		if (ft_strncmp(line, color_map[j].prefix, 2))
			continue ;
		if ((*(color_map[j]).color) != -1)
		{
			ft_eprintf(ERR"%s color set multiple times\n", color_map[j].prefix);
			return (free(line), ERROR);
		}
		if (!extract_and_parse_colors(color_map[j].color, line))
			return (free(line), ERROR);
		return (SUCCESS);
	}
	return (SUCCESS);
}
