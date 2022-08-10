/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:17:25 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/10 21:35:41 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
#define CUBE_H
#define  SIZE_ 15
#define  SIZE_PLYR 5
#define  WALL_DIFF 0.0005
#define  WIDTH 1500
#define  HEIGHT 1000
#define  MINI_MAP_WIDTH 12
#define  MINI_MAP_HEIGHT 12
#define  ANGLE_VIEW M_PI /3
#define  COL_PLAYER 0xff9933
#define  WALK_SPEED 0.19
#define  ROTATE_SPEED 0.08
#define  SHADING 50


#include <mlx.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"

typedef struct	s_ray {
	int		id;
	float	x;
	float	y;
	float	distance;
	char	status;
	float	wallheigth;
	struct s_ray	*next;
}	t_ray;

typedef struct	s_player {
	float	x;
	float	y;
	int	turndirection;
	int	walkdirection;
	int	sidedirection;
	float rotatedirection;
	float rotatespeed;
	float walkspeed;
	float	h_x;
	float 	h_y;
	float	v_x;
	float 	v_y;
	float	h_distance;
	float	v_distance;
}	t_player;

typedef struct s_texture
{
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	int F;
	int C;
}	t_texture;
typedef struct	s_data {
	void	*mlx;
	void	*wind;
	void	*img;
	void	*img1;
	void	*ray_h;
	void	*ray_v;
	char	*addr;
	char 	*wall;
	int		bits_per_pixel;
	int		line_length;
	int		line_length_wall;
	int		endian;
	int		row;
	int		col;
	char	**map;
	int 	x;
	int 	y;
	t_player player;
	t_texture texture;
}	t_data;

void mini_map(t_data *data, t_ray *ray);
//utils.c
void	put_pixel(t_data *data,char *buffer, int color, int x, int y, int alpha);
int 	is_wall(t_data *data, int x, int y);
int		is_player(char c);
int		point_in_range(t_data *data, int x, int y);
int	check_wall(t_data *data, char status);
int	mini_map_range(int x, int y);
//keycode.c
int keyprelease(int keycode, void *parm);
int keypress(int keycode, void *parm);
//ray_list.c
t_ray	*new_ray(int id, float x, float y, float distance, char status);
void	add_ray(t_ray **list, t_ray *ray);
void	clear_rays(t_ray **list);
t_ray	*update_ray(t_data *data);
//read_map.c
void	read_map(t_data *data);
void	initial(t_data *data);
void	get_info(t_data *data);
//rendring.c
void rendring(t_data *data, t_ray *ray);

void	horizontal_initial_points(t_data *data, float angle);
void	vertical_initial_points(t_data *data, float angle);
void	horizontal_points(t_data *data, float angle);
void	vertical_points(t_data *data, float angle);
#endif
