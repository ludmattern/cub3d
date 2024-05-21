/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:00:32 by lmattern          #+#    #+#             */
/*   Updated: 2024/05/21 14:54:58 by lmattern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
this function parses the map from the .cub file checking for invalid characters.
*/
static int	parse_map(t_cub *cub)
{
	char	*line;
	char	**lines;

	if (!skip_empty_lines(cub->filefd, &line))
		return (ERROR);
	if (!extract_map_lines(cub, &line, &lines)
		|| !check_end_of_file(cub->filefd, &line))
		return (clean_return(line, lines, ERROR));
	if (!parse_lines(cub, lines))
		return (clean_return(line, lines, ERROR));
	return (clean_return(line, lines, SUCCESS));
}

/*
this function parses the .cub file and checks if the map is valid.
*/
static int	parsing_data(t_cub *cub)
{
	if (!parse_parameters(cub))
		return (ERROR);
	if (!parse_map(cub))
		return (ERROR);
	if (!check_map_validity(&cub->map))
		return (ERROR);
	close(cub->filefd);
	return (SUCCESS);
}

/*
this program is a 3D representation of a maze using raycasting.
it uses the minilibx library to create a window and draw the maze.
the maze and the textures are parsed from a .cub file.
the player can move in the maze and rotate the camera.
the input must be a .cub file.
*/
int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = init_cub_data_struct();
	if (!check_program_args(argc, argv)
		|| !ft_check_extension(argv[0], argv[1], ".cub")
		|| !check_submitted_file(argv[1], &cub->filefd))
		return (clean_exit(cub, EXIT_FAILURE));
	if (!parsing_data(cub))
		return (clean_exit(cub, EXIT_FAILURE));
	start_exec(cub);
	ft_free_double_int_array(cub->map.grid, cub->map.height);
	return (clean_exit(cub, EXIT_SUCCESS));
}
