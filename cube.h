/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:17:25 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/20 16:09:42 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
#define CUBE_H
#define  SIZE_ 10
#define  SIZE_PLYR 5
#define  WIDTH 1200
#define  HEIGHT 800
#define  MINI_MAP_WIDTH 12
#define  MINI_MAP_HEIGHT 12
#define  ANGLE_VIEW M_PI / 3
#define  WALK_SPEED 0.2
#define  ROTATE_SPEED 0.07


#include <mlx.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"

typedef struct	s_ray {
	float	x;
	float	y;
	float	distance;
	char    status;
	float	wallheigth;
	struct s_ray	*next;
}	t_ray;

typedef struct	s_player {
	float	x;
	float	y;
	int		turndirection;
	int		walkdirection;
	int		sidedirection;
	float 	rotatedirection;
	float	rotatespeed;
	float 	walkspeed;
	float	h_x;
	float 	h_y;
	float	v_x;
	float 	v_y;
	float	h_distance;
	float	v_distance;
	float	mouse;
	int	shoot;
}	t_player;

typedef struct s_texture
{
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	int	F;
	int	C;
	void *Door;
	void	*wall_NO;
	void	*wall_SO;
	void	*wall_EA;
	void	*wall_WE;
	void	*gun;
	char 	*gun_buff;
	int		gun_w;
	int		gun_h;
	int		gun_size;
	char 	*wall_buff;
	int		no_w;
	int		no_h;
	int		so_w;
	int		so_h;
	int		ea_w;
	int		ea_h;
	int		we_w;
	int		we_h;
	int		door_w;
	int		door_h;
}	t_texture;
typedef struct	s_data {
	void		*mlx;
	void		*wind;
	void		*img;
	char		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		line_length_wall;
	int		line_length_door;
	int		endian;
	int		row;
	int		col;
	char	**map;
	char	*mapath;
	float	mid_ray_d;
	char		status;
	t_player	player;
	t_texture	texture;
}	t_data;

void 	mini_map(t_data *data, t_ray *ray);
//utils.c
void		put_pixel(t_data *data,char *buffer, int color, int x, int y, int alpha);
int is_wall(t_data *data, int x, int y);
int		is_player(char c);
int		point_in_range(t_data *data, int x, int y);
int		check_wall(t_data *data, char status);
int		mini_map_range(int x, int y);
void		ft_free(char **table);
int		is_texture(char *line);
//keycode.c
int		keyprelease(int keycode, void *parm);
int		keypress(int keycode, void *parm);
int		mouse_hook(int x,int y,void *param);
//ray_list.c
t_ray	*new_ray(t_ray holder);
void		add_ray(t_ray **list, t_ray *ray);
void		clear_rays(t_ray **list);
t_ray	*update_ray(t_data *data);
//read_map.c
void		read_map(t_data *data);
void		map_parsing(t_data *data, char *line, char **tmp_map, int fd);
void		initial(t_data *data);
void		get_info(t_data *data);
void		check_walls(t_data *data);
void		ft_error(t_data *data, char *msg);
//rendring.c
void 	rendring(t_data *data, t_ray *ray);

void		horizontal_initial_points(t_data *data, float angle);
void		vertical_initial_points(t_data *data, float angle);
void		horizontal_points(t_data *data, float angle);
void		vertical_points(t_data *data, float angle);

void sprite_gun(t_data *data);

#endif
