/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cub3d.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: amonteli <amonteli@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/30 21:55:06 by amonteli     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 04:41:30 by amonteli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

/*
**	Configurations key in map.cub
*/

enum					e_conf
{
	R = (1 << 0),
	T_NO = (1 << 1),
	T_SO = (1 << 2),
	T_WE = (1 << 3),
	T_EA = (1 << 4),
	T_S = (1 << 5),
	F = (1 << 6),
	C = (1 << 7),
};

/*
** 	Enum
**	Colored Textures. (RGB Textures)
*/

enum					e_colored_textures
{
	FLOOR,
	SKY
};

/*
**	union for get RGB color
**	assign color by t_color.rgb.KEY = INT;
**	get int RGB by t_color.c;
*/

typedef union			u_color
{
	unsigned int		c;
	struct				s_rgb
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	}					rgb;
}						t_color;

typedef struct			s_game
{
	void				*mlx;
	void				*window;
	int					screen;
	int					width;
	int					height;
	int					conf;
	t_color				*colors[2];
}						t_game;

/*
** 	srcs/cub3d.c
*/

int						main(int argsc, char **args);
void					exit_programs(t_game *vars, char *str);


/*
** 	srcs/parser.c
*/

int						parse(t_game *vars, int argc, char **args);
void					parse_configuration(t_game *vars, int fd);


#endif