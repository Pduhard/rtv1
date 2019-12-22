/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rtv1.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/21 21:06:00 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/22 07:17:47 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>
# include <pthread.h>

# define WIN_WIDTH	640
# define WIN_HEIGHT	480

/* CST MACROS */
# define _M_PI_180	0.01745329251

typedef	enum	{OBJ_SPHERE} e_obj_type;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*img_str;
	int			bpp;
	int			s_l;
	int			endian;
}				t_mlx;

typedef struct	s_44matf
{
	float		val[4][4];
}				t_44matf;

typedef struct	s_3vecf
{
	float		val[3];
}				t_3vecf;

typedef struct	s_2vecf
{
	float		val[2];
}				t_2vecf;

typedef struct	s_sphere
{
	float		x;
	float		y;
	float		z;
	float		radius;
}				t_sphere;

typedef struct	s_obj
{
	e_obj_type	obj_type;
	void		*obj_param;
	int			color;
}				t_obj;

typedef struct	s_light
{
	t_3vecf		intensity;
	t_3vecf		position;
	t_3vecf		color;
	t_44matf	l_to_world;
	t_3vecf		dir;
}				t_light;

typedef struct	s_data
{
	t_mlx		*mlx;
	t_obj		*objs;
	t_light		*lights;
	float		fov;
	t_44matf	camera_to_world;
}				t_data;

t_data	*init_data(void);
void	init_camera_to_world_matrix(float mat[4][4]);
void	init_light_to_world_matrix(float mat[4][4]);
void	render(t_data *data);

t_3vecf	assign_3vecf(float x, float y, float z);
void	normalize_3vecf(t_3vecf *vec);
t_3vecf	sub_3vecf(t_3vecf a, t_3vecf b);
float	dot_product_3vecf(t_3vecf a, t_3vecf b);

void	mult_vec_matrix(t_3vecf, t_44matf mat, t_3vecf *dst);
void	mult_dir_matrix(t_3vecf, t_44matf mat, t_3vecf *dst);

float	degree_to_radian(float degree);

#endif
