/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_steps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:00:32 by lmattern          #+#    #+#             */
/*   Updated: 2024/05/21 13:19:00 by lmattern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*
this function checks if the program has the right number of arguments
*/
int	check_program_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_eprintf(ERR"%s only accepts one argument\n", \
		argv[0] + skip_prefix(argv[0]));
		return (ERROR);
	}
	return (SUCCESS);
}

/*
this function checks if the file is a valid .cub file
*/
int	check_submitted_file(char *file, int *filefd)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_eprintf(ERR"%s is not a valid file\n", file), ERROR);
	*filefd = fd;
	return (SUCCESS);
}

/*
this function initializes the cub data structure and returns it
*/
t_cub	*init_cub_data_struct(void)
{
	t_cub	*cub;

	cub = ft_calloc(1, sizeof(t_cub));
	if (!cub)
	{
		ft_eprintf(ERR"%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	cub->filefd = -1;
	cub->styles.floor = -1;
	cub->styles.ceiling = -1;
	return (cub);
}
