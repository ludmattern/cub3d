/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:00:32 by lmattern          #+#    #+#             */
/*   Updated: 2024/05/20 09:11:15 by lmattern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int	extract_and_parse_texture(char **texture, const char *line)
{
	size_t	i;
	size_t	len;

	i = 3;
	len = ft_strlen(line);
	while (ft_isspace(line[i]))
		i++;
	if (line[len - 1] == '\n')
		*texture = ft_strndup(line + i, len - i - 1);
	else
		*texture = ft_strdup(line + i);
	if (!*texture)
		return (ft_eprintf(ERR ALLOC_ERR" for texture\n"), ERROR);
	return (SUCCESS);
}

static void	init_texture_map(t_texture_map	*texture_map, t_cub *cub)
{
	texture_map[0] = (t_texture_map){"NO ", &cub->textures.no};
	texture_map[1] = (t_texture_map){"SO ", &cub->textures.so};
	texture_map[2] = (t_texture_map){"WE ", &cub->textures.we};
	texture_map[3] = (t_texture_map){"EA ", &cub->textures.ea};
	texture_map[4] = (t_texture_map){NULL, NULL};
}

static int	check_texture_path(char *path, char *type)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_eprintf(ERR"%s is not valid %s path\n", path, type), ERROR);
	close(fd);
	return (SUCCESS);
}

int	process_texture(t_cub *cub, char *line)
{
	size_t			j;
	t_texture_map	texture[5];

	j = -1;
	init_texture_map(texture, cub);
	while (texture[++j].prefix)
	{
		if (ft_strncmp(line, texture[j].prefix, 3))
			continue ;
		if (*(texture[j].texture))
		{
			ft_eprintf(ERR"%stexture set multiple times\n", texture[j].prefix);
			return (free(line), ERROR);
		}
		if (!extract_and_parse_texture(texture[j].texture, line))
			return (free(line), ERROR);
		if (!check_texture_path(*(texture[j].texture), "texture"))
			return (free(line), ERROR);
		return (SUCCESS);
	}
	return (SUCCESS);
}
