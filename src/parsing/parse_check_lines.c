/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:00:32 by lmattern          #+#    #+#             */
/*   Updated: 2024/05/21 11:13:11 by lmattern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
this function checks if the line contains invalid characters and if the player
is set correctly.
*/
static int	check_line_char(char *line)
{
	int			i;
	static bool	player = false;

	i = 0;
	if (!line)
		return (SUCCESS);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != '\n')
		{
			ft_eprintf(ERR"Invalid character in map : %c\n", line[i]);
			return (ERROR);
		}
		if (!player && (line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'E' || line[i] == 'W'))
			player = true;
		else if (player && (line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'E' || line[i] == 'W'))
			return (ft_eprintf(ERR"Multiple players\n"), ERROR);
		i++;
	}
	return (SUCCESS);
}

/*
this function checks if the map is not too small and if the player is present.
*/
static int	last_checks(t_cub *cub, bool player, char *line)
{
	ft_free(line);
	if (cub->map.height < 3)
		return (ft_eprintf(ERR"Map is too small\n"), ERROR);
	if (!player)
		return (ft_eprintf(ERR"Player is missing\n"), ERROR);
	return (SUCCESS);
}

/*
this function extracts the map lines from the .cub file and checks if the map
is well formatted.
*/
int	extract_map_lines(t_cub *cub, char **line, char ***lines)
{
	size_t	i;
	bool	player;

	i = 0;
	*lines = NULL;
	player = false;
	while (1)
	{
		if (!check_line_char(*line))
			return (ERROR);
		*lines = ft_realloc(*lines, i * sizeof(char *), \
		(i + 2) * sizeof(char *));
		if (!*lines)
			return (ft_eprintf(ERR ALLOC_ERR" for map\n"), ERROR);
		(*lines)[i++] = *line;
		cub->map.height++;
		if (ft_strchr(*line, 'N') || ft_strchr(*line, 'S')
			|| ft_strchr(*line, 'E') || ft_strchr(*line, 'W'))
			player = true;
		*line = get_next_line(cub->filefd);
		if (!*line || !**line || **line == '\n')
			break ;
	}
	return (last_checks(cub, player, *line));
}

/*
this function checks if the map is not cut off by empty lines.
*/
int	check_end_of_file(int fd, char **line)
{
	while (1)
	{
		*line = get_next_line(fd);
		if (*line && **line != '\n')
			return (ft_eprintf(ERR"Map is not well formatted\n"), ERROR);
		if (!*line || !**line)
			break ;
		free(*line);
	}
	return (SUCCESS);
}

/*
this function skips empty lines in the .cub file and returns an error if the map
is missing.
*/
int	skip_empty_lines(int fd, char **line)
{
	*line = NULL;
	while (1)
	{
		*line = get_next_line(fd);
		if (!line || !*line)
		{
			ft_eprintf(ERR"Map is missing\n");
			return (get_next_line(-1), ERROR);
		}
		if ((*line)[0] != '\n')
			break ;
		free(*line);
	}
	return (SUCCESS);
}
