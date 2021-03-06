/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 09:20:44 by amonteli          #+#    #+#             */
/*   Updated: 2020/10/24 03:57:48 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/includes/libft.h"
# include "../mlx/mlx.h"

# define TEXTURES 5
# define MAP_POSITION_TYPE "NSWE"
# define MAP_FLAGS "NSWE201 \n"

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

enum					e_key
{
	MV_UP = (1 << 0),
	MV_DOWN = (1 << 1),
	MV_LEFT = (1 << 2),
	MV_RIGHT = (1 << 3),
	LEFT = (1 << 4),
	RIGHT = (1 << 5),
};

enum					e_keycode
{
	KEY_ESCAPE = 65307,
	KEY_MOVE_UP = 119,
	KEY_MOVE_DOWN = 115,
	KEY_MOVE_LEFT = 97,
	KEY_MOVE_RIGHT = 100,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363
};

enum					e_colored_textures
{
	FLOOR,
	SKY
};

enum					e_textures
{
	SOUTH,
	NORTH,
	EAST,
	WEST,
	SPRITE
};

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

typedef	struct			s_textures
{
	int					width;
	int					height;
	int					bpp;
	int					size;
	int					endian;
	void				*img;
	int					*data;
}						t_textures;

typedef	struct			s_sprite
{
	int					pos_x;
	int					pos_y;
	float				distance;
}						t_sprite;

typedef	struct			s_bmp
{
	int					width;
	int					height;
	unsigned int		bytes_count;
	int					width_in_bytes;
	unsigned int		image_size;
	unsigned int		bytes_size;
	unsigned int		bfoffbits;
	unsigned int		file_size;
	unsigned int		biplanes;
	unsigned char		header[54];
	int					fd;
}						t_bmp;

typedef struct			s_game
{
	void				*mlx;
	void				*window;
	int					screen;
	int					width;
	int					height;
	int					conf;
	t_color				colors[2];

	char				*paths[5];
	t_textures			textures[5];

	char				**map;
	char				*map_buf;

	void				*img;
	int					*img_data;

	char				pos_type;

	float				posx;
	float				posy;
	float				dirx;
	float				diry;

	float				camerax;

	float				raydirx;
	float				raydiry;

	float				cam_plane_x;
	float				cam_plane_y;

	float				sidedistx;
	float				sidedisty;
	float				deltadistx;
	float				deltadisty;
	float				perpwalldist;

	float				time;
	float				old_time;
	float				old_dir_x;
	float				old_cam_plane_x;

	int					mapx;
	int					mapy;
	int					stepx;
	int					stepy;
	int					hit;
	int					side;

	int					lineheight;
	int					drawstart;
	int					drawend;

	float				x;
	int					wall_height;
	unsigned char		key;

	float				move_speed;
	float				rotation_speed;

	t_sprite			*sprites;
	int					sprites_count;
	float				*perp_buffer;

	int					sprite_index;

	float				sprite_x;
	float				sprite_y;

	float				invdet;

	float				transform_x;
	float				transform_y;

	int					sprite_screen_x;

	int					sprite_width;
	int					sprite_height;

	int					sprite_drawstart_x;
	int					sprite_drawstart_y;

	int					sprite_drawend_x;
	int					sprite_drawend_y;

	int					sprite_stripe;
	int					sprite_d;

	t_bmp				*bmp;
	int					map_height;

	float				wallx;
	int					texturex;
	float				step;
	float				texturepos;
	float				texturey;

	int					sprite_texturex;
	int					sprite_texturey;
	unsigned int		sprite_color;
	int					sprite_yi;
}						t_game;

/*
 **	parser/parser.c
*/

void					parse_file(t_game *vars, char *filename);

/*
**	parser/args_parser.c
*/

void					check_params(t_game *vars, int argc, char **args);

/*
**	parser/configuration_manager.c
*/

void					parse_configuration(t_game *vars, int fd);

/*
**	parser/map_parser.c
*/

void					parse_map(t_game *vars, int fd);

/*
**	parser/parser_utils.c
*/

int						is_only_resolution(char *line);
void					check_screen_size(t_game *vars);
void					check_map_hole(t_game *vars,
char **map, int pos, size_t size);

/*
**	parser/sprite_parser.c
*/

void					parse_sprite(t_game *vars);

/*
**	utils/exit_manager.c
*/

void					exit_program(t_game *vars, char *reason);
void					clean_exit(t_game *vars);

/*
**	utils/utilities.c
*/

int						is_valid_configuration(t_game *vars);
t_color					create_color(int r, int g, int b);
float					ft_fabs(float number);
void					assign_side(t_game *vars);
void					sprite_fill_img_data(t_game *vars);

int						is_valid_map(t_game *vars);

/*
**	=============================
**
**			  ENGINE
**
**  =============================
*/

/*
**	engine/window_manager.c
*/

void					open_window(t_game *vars);
int						close_window(t_game *vars);

/*
**	engine/keyboard_manager.c
*/

int						key_press(int key_code, t_game *vars);
int						key_release(int key_code, t_game *vars);
int						key_loop_controller(t_game *vars);

/*
**	engine/movement_manager.c
*/

void					move_player_left(t_game *vars);
void					move_player_right(t_game *vars);
void					move_player_up(t_game *vars);
void					move_player_down(t_game *vars);

/*
**	engine/rotation_manager.c
*/

void					rotate_player_camera_to_left(t_game *vars);
void					rotate_player_camera_to_right(t_game *vars);

/*
**	engine/ui/raycast.c
*/

int						raycast(t_game *vars);

/*
**	engine/ui/init_raycast.c
*/

void					initiate_raycast_and_mlx_data(t_game *vars);

/*
**	engine/ui/raycast_drawer.c
*/

void					raycast_draw(t_game *vars);

void					draw_sprites(t_game *vars);

void					init_bmp(t_game *vars);
void					save_bmp(t_game *vars);

#endif
