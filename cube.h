/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:17:25 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/08 07:42:05 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
#define CUBE_H
#define  SIZE_ 15
#define  SIZE_PLYR 3
#define  WIDTH 1000
#define  HEIGHT 700
#define  ANGLE_VIEW M_PI/3


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

typedef struct	s_data {
	void	*mlx;
	void	*wind;
	void	*img;
	void	*ray_h;
	void	*ray_v;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		line_length_view;
	int		endian;
	int		row;
	int		col;
	char	**map;
	int 	x;
	int 	y;
	t_player player;
}	t_data;

void	read_map(t_data *data);
void	initial(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		is_player(char c);
int		draw(t_data *data);
t_ray	*update_ray(t_data *data);
void	draw_background(t_data *data);
void	save_walls_position(t_data *data);
void	horizontal_initial_points(t_data *data, float angle);
void	vertical_initial_points(t_data *data, float angle);
void	horizontal_points(t_data *data, float angle);
void	vertical_points(t_data *data, float angle);
int	point_in_range(t_data *data, int x, int y);
int check_wall_points(t_data *data, int x, int y);

void	draw_player(t_data *data, t_ray *ray);
void	get_info(t_data *data);
#endif
