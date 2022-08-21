/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:17:25 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/21 17:41:20 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# define  SIZE_ 10
# define  SIZE_PLYR 5
# define  WIDTH 1200
# define  HEIGHT 800

# include <mlx.h>
# include <pthread.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

typedef struct s_point {
	int	x;
	int	y;
}	t_point;

typedef struct s_ray {
	float			x;
	float			y;
	float			distance;
	char			status;
	float			wallheigth;
	struct s_ray	*next;
}	t_ray;

typedef struct s_player {
	float	x;
	float	y;
	int		turndirection;
	int		walkdirection;
	int		sidedirection;
	float	rotatedirection;
	float	rotatespeed;
	float	walkspeed;
	float	h_x;
	float	h_y;
	float	v_x;
	float	v_y;
	float	h_distance;
	float	v_distance;
	float	mouse;
	int		shoot;
}	t_player;

typedef struct s_texture {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		sky;
	void	*wall_no;
	char	*wall_buff;
	void	*wall_so;
	void	*wall_ea;
	void	*wall_we;
	int		wall_w;
	int		wall_h;
	char	*gun_buff;
	void	*gun;
	int		gun_size;
	int		gun_w;
	int		gun_h;
}	t_texture;

typedef struct s_data {
	void		*mlx;
	void		*wind;
	void		*img;
	char		*addr;
	int			line_length_wall;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			row;
	int			col;
	char		**map;
	char		*mapath;
	float		mid_ray_d;
	char		status;
	t_player	player;
	t_texture	texture;
	t_point		point;
}	t_data;

void	mini_map(t_data *data, t_ray *ray);
void	put_pixel(t_data *data, int color, int alpha);
void	ft_free(char **table);
void	ft_exit(t_data *data, char *msg);
void	set_point(t_data *data, int x, int y);
void	add_ray(t_ray **list, t_ray *ray);
void	clear_rays(t_ray **list);
void	read_map(t_data *data);
void	map_parsing(t_data *data, char *line, char **tmp_map, int fd);
void	initial(t_data *data);
void	get_info(t_data *data);
void	check_walls(t_data *data);
void	rendring(t_data *data, t_ray *ray);
void	horizontal_initial_points(t_data *data, float angle);
void	vertical_initial_points(t_data *data, float angle);
void	horizontal_points(t_data *data, float angle);
void	vertical_points(t_data *data, float angle);
void	sprite_gun(t_data *data);
t_ray	*new_ray(float x, float y, float distance, char status);
t_ray	*update_ray(t_data *data);
int		check_wall(t_data *data, char status);
int		color_convert(char *buff, int lenght, int i, int j);
int		is_transparent(t_data *data, int pixel);
int		is_wall(t_data *data, int x, int y);
int		is_player(char c);
int		point_in_range(t_data *data, int x, int y);
int		is_texture(char *line);
int		keyprelease(int keycode, void *parm);
int		keypress(int keycode, void *parm);
int		mouse_hook(int x, int y, void *param);

#endif
