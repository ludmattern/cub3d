/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:00:32 by lmattern          #+#    #+#             */
/*   Updated: 2024/05/20 16:09:48 by fprevot          ###   ########.fr       */
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
	ft_free_double_int_array(cub->map.grid, cub->map.height);
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
	return (clean_exit(cub, EXIT_SUCCESS));
}

/*
Votre programme doit prendre en premier argument un fichier de description de
scène avec pour extension .cub
◦ La map doit être composée d’uniquement ces 6 caractères : 0 pour les espaces
vides, 1 pour les murs, et N,S,E ou W qui représentent la position de départ
du joueur et son orientation.
Cette simple map doit être valide :
111111
100101
101001
1100N1
111111

◦ La map doit être fermée/entourée de murs, sinon le programme doit renvoyer une erreur.
◦ Mis à part la description de la map, chaque type d’élément peut être séparée par une ou plusieurs lignes vides.
◦ La description de la carte sera toujours en dernier dans le fichier, le reste des éléments peut être dans n’importe quel ordre.
◦ Sauf pour la map elle-même, les informations de chaque élément peuvent être séparées par un ou plusieurs espace(s).
◦ La carte doit être parsée en accord avec ce qui est présenté dans le fichier. Les espaces sont une partie valable de la carte, c’est à vous de les gérer correctement.
Vous devez pouvoir parser n’importe quelle sorte de carte, tant qu’elle respecte les règles de carte.


◦ Pour chaque élement, le premier caractère est l’identifiant (un ou deux caractères)

suivi de toutes les informations spécifiques à l’élément dans un ordre strict tel que :

— texture nord : NO ./path_to_the_north_texture
	— identifiant : NO
	— chemin vers la texture nor

— South texture : SO ./path_to_the_south_texture
	— identifiant : SO
	— chemin vers la texture sud

— West texture : WE ./path_to_the_west_texture
	— identifiant : WE
	— chemin vers la texture ouest

— East texture : EA ./path_to_the_east_texture
	— identifiant : EA
	— chemin vers la texture est

— Couleur du sol : F 220,100,0
	— identifiant : F
	— couleurs R,G,B range [0,255] : 0, 255, 255

— Couleur du plafond : C 225,30,0
	— identifiant : C
	— couleurs R,G,B range [0,255] : 0, 255, 255

tant que les identifiant ne sont pas tous trouves
  lire ligne
	si ligne vide
		continuer
	si identifiant
		verifier identifiant
				si texture
					verifier chemin
				si couleur
					verifier couleur
		si pas identifiant
			erreur
*/