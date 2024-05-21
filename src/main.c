/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:00:32 by lmattern          #+#    #+#             */
/*   Updated: 2024/05/21 11:31:14 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

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
