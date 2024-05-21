/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:00:32 by lmattern          #+#    #+#             */
/*   Updated: 2024/05/21 12:50:55 by lmattern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
this function checks if the necessary parameters are present in the .cub file.
*/
static bool	is_missing_parameters(t_cub *cub)
{
	if (cub->styles.floor == -1
		|| cub->styles.ceiling == -1
		|| !cub->textures.no
		|| !cub->textures.so
		|| !cub->textures.we
		|| !cub->textures.ea)
		return (true);
	return (false);
}

/*
this function processes the line from the .cub file and calls the right function
*/
static int	process_line(t_cub *cub, char *line)
{
	if (!line)
		return (ft_eprintf(ERR"Missing or invalid parameters\n"), ERROR);
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (process_texture(cub, line));
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (process_style(cub, line));
	else if (line[0] == '\n')
		return (SUCCESS);
	ft_eprintf(ERR"Missing or invalid parameters\n");
	return (free(line), ERROR);
}

/*
this function parses the parameters from the .cub file.
*/
int	parse_parameters(t_cub *cub)
{
	char	*line;

	while (is_missing_parameters(cub))
	{
		line = get_next_line(cub->filefd);
		if (!process_line(cub, line))
			return (get_next_line(-1), ERROR);
		ft_free(line);
	}
	return (SUCCESS);
}
