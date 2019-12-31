/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rtv1.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/21 21:06:00 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/31 13:23:04 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>
# include <pthread.h>
# include <fcntl.h>
# include <float.h>
# define WIN_WIDTH	600
# define WIN_HEIGHT	600

/* CST MACROS */
# define _M_PI_180	0.01745329251

/* HOOKS MACRO */
# define A_KEY	1
# define D_KEY	(1 << 1)
# define W_KEY	(1 << 2)
# define S_KEY	(1 << 3)
# define F_KEY	(1 << 4)
# define G_KEY	(1 << 5)

typedef	enum	{OBJ_SPHERE, OBJ_PLANE} e_obj_type;
typedef	enum	{LIGHT_POINT, LIGHT_AMBIENT, LIGHT_DIRECTIONAL} e_light_type;

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

typedef struct	s_33matf
{
	float		val[3][3];
}				t_33matf;

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
	t_3vecf		origin;
	float		radius;
}				t_sphere;

typedef struct	s_plane
{
	t_3vecf		origin;
	t_3vecf		normal;
}				t_plane;

typedef struct	s_cone
{
	t_3vecf		origin;
	t_3vecf		normal;
}				t_cone;

typedef struct	s_obj
{
	e_obj_type	obj_type;
	void		*obj_param;
	int			(*ray_intersect)(t_3vecf, t_3vecf, struct s_obj *, float *, float, float);
	t_3vecf		(*get_normal_inter)(t_3vecf, struct s_obj *);
	t_3vecf		color;
//	int			color;
	struct s_obj	*next;
}				t_obj;

typedef struct	s_light
{
	e_light_type	light_type;
	t_3vecf		intensity;
	t_3vecf		position;
	t_3vecf		origin;
	t_3vecf		color;
	t_44matf	l_to_world;
	t_3vecf		dir;
	struct s_light	*next;
}				t_light;

typedef struct	s_cam
{
	float		fov;
	t_44matf	camera_to_world;
	t_3vecf		origin;
	t_3vecf		rotation;
}				t_cam;

typedef struct	s_data
{
	t_mlx		*mlx;
	t_cam		*camera;
	t_obj		*objs;
	t_light		*lights;
	float		fov;
	t_44matf	camera_to_world;
	char		*scene_name;
	int			hooks;
	t_33matf	rot_mat[3];
	float		mouse_x;
	float		mouse_y;
}				t_data;

t_data	*init_data(char *file_name);
void	init_camera_to_world_matrix(float mat[4][4]);
void	init_light_to_world_matrix(float mat[4][4]);
t_33matf	init_rotation_matrix_x(float theta);
t_33matf	init_rotation_matrix_y(float theta);
t_33matf	init_rotation_matrix_z(float theta);

void	render(t_data *data);

int		parse_rt_conf(char *file_name, t_data *data);
int		parse_3vecf(char *line, int i, t_3vecf *vec);
int		parse_float(char *line, int i, float *val);

int		parse_sphere(char *line, t_data *data);
int		parse_plane(char *line, t_data *data);

t_3vecf	assign_3vecf(float x, float y, float z);
void	normalize_3vecf(t_3vecf *vec);
float	get_length_3vecf(t_3vecf vec);
t_3vecf	sub_3vecf(t_3vecf a, t_3vecf b);
float	dot_product_3vecf(t_3vecf a, t_3vecf b);

t_3vecf	mult_3vecf_33matf(t_3vecf vect, t_33matf mat);
t_33matf	mult_33matf_33matf(t_33matf a, t_33matf b);
void	mult_vec_matrix(t_3vecf, t_44matf mat, t_3vecf *dst);
void	mult_dir_matrix(t_3vecf, t_44matf mat, t_3vecf *dst);

float	degree_to_radian(float degree);

int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);
int		moov_hook(int x, int y, void *param);
int		print_loop_image(void *param);

#endif
