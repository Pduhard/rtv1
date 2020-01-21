/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rtv1.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/21 21:06:00 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/21 09:02:11 by aplat       ###    #+. /#+    ###.fr     */
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
# define WIN_WIDTH	800
# define WIN_HEIGHT	800
# define NB_THREADS	8

/* CST MACROS */
# define _M_PI_180	0.01745329251

/* HOOKS MACRO */
# define A_KEY	0b1
# define D_KEY	0b10
# define W_KEY	0b100
# define S_KEY	0b1000
# define F_KEY	0b10000
# define G_KEY	0b100000

# define ARR_LEFT_KEY	0b1000000
# define ARR_RIGHT_KEY	0b10000000
# define ARR_DOWN_KEY	0b100000000
# define ARR_UP_KEY		0b1000000000

# define SPACE_KEY	0b10000000000
# define SHIFT_KEY	0b100000000000

# define ESC_KEY 0x0035

/* ERROR MSG */
# define ERRORSIZE "WIN_Size: Min 400/400, Max 2560/1420\n"
# define ERRORARG  "Usage: ./rtv1 NameFile.rt_conf\n"
# define SERRORNAME "Syntax error: name syntax: name(scene_name)\n"
# define SERRORCAM "Syntax error: camera syntax: camera(origin)(rotation)\n"
# define SERRORLIGHT "Syntax error: light syntax: light(light_type)(origin)(intensity)\n"
# define SERRORCYL "Syntax error: cylinder syntax: cylinder(center)(tip)(radius)(color)\n"
# define SERRORSPHERE "Syntax error: sphere syntax: sphere(origin)(radius)(color)\n"
# define SERRORPLANE "Syntax error: plane syntax: plane(origin)(normal)(color)\n"
# define SERRORCONE "Syntax error: cone syntax: cone(center)(tip)(radius)(color)\n"

typedef	enum	{OBJ_SPHERE, OBJ_PLANE, OBJ_CONE, OBJ_CYLINDER} e_obj_type;
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
	t_3vecf		center;
	t_3vecf		tip;
	float		radius;
	float		m;
	t_3vecf		h;
	t_3vecf		norm_h;
	float		h_length;
}				t_cone;

typedef struct	s_cylinder
{
	t_3vecf		center;
	t_3vecf		tip;
	float		radius;
	t_3vecf		h;
	t_3vecf		norm_h;
	float		radius2;
}				t_cylinder;

typedef	struct	s_polynome
{
	float	a;
	float	b;
	float	c;
	float	dp_dir_norm_h;
	float	dp_w_norm_h;
	t_3vecf	w;
	float	delta;
	t_2vecf	hit_point;
}				t_polynome;

typedef struct	s_obj
{
	e_obj_type	obj_type;
	void		*obj_param;
	int			(*ray_intersect)(t_3vecf, t_3vecf, struct s_obj *, float *, float, float);
	t_3vecf		(*get_normal_inter)(t_3vecf, struct s_obj *);
	t_3vecf		color;
	struct s_obj	*next;
}				t_obj;

typedef struct	s_light
{
	e_light_type	light_type;
	float		intensity;
	t_3vecf		position;
	t_3vecf		origin;
	t_3vecf		dir;
	struct s_light	*next;
}				t_light;

typedef struct	s_cam
{
	t_3vecf		origin;
	t_2vecf		rotation;
}				t_cam;

typedef struct	s_data
{
	t_mlx		*mlx;
	t_cam		*camera;
	t_obj		*objs;
	t_light		*lights;
	char		*scene_name;
	int			hooks;
	t_33matf	rot_mat[2];
}				t_data;

typedef struct	s_thread
{
	t_data		*data;
	int			start;
	int			end;
}				t_thread;

t_data	*init_data(char *file_name);
t_33matf	init_rotation_matrix_y(float theta);
t_33matf	init_rotation_matrix_vec(t_3vecf vec, double theta);
void	init_threads(t_thread threads[NB_THREADS], t_data *data);

void	render(t_data *data);

int		parse_rt_conf(char *file_name, t_data *data);
int		parse_3vecf(char *line, int i, t_3vecf *vec);
int		parse_2vecf(char *line, int i, t_2vecf *vec);
int		parse_float(char *line, int i, float *val);

int		parse_sphere(char *line, t_data *data);
int		parse_plane(char *line, t_data *data);
int		parse_cone(char *line, t_data *data);
int		parse_cylinder(char *line, t_data *data);

void	set_cone(t_cone *c);
t_polynome	polynome_cone(t_3vecf orig, t_3vecf dir, t_cone c);

void	set_cylinder(t_cylinder *c);
t_polynome	polynome_cylinder(t_3vecf orig, t_3vecf dir, t_cylinder c);

t_polynome	polynome_sphere(t_3vecf dir, t_sphere s, t_3vecf dist);

t_3vecf	assign_3vecf(float x, float y, float z);
void	normalize_3vecf(t_3vecf *vec);
float	get_length_3vecf(t_3vecf vec);
t_3vecf	sub_3vecf(t_3vecf a, t_3vecf b);
t_3vecf	product_3vecf(t_3vecf a, t_3vecf b);
float	dot_product_3vecf(t_3vecf a, t_3vecf b);
t_3vecf	invert_3vecf(t_3vecf vec);
t_3vecf productadd_3vecf(t_3vecf a, t_3vecf b, float c);
t_3vecf productwf_3vecf(t_3vecf a, float b);

t_3vecf	mult_3vecf_33matf(t_3vecf vect, t_33matf mat);
float	degree_to_radian(float degree);

int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);
int		print_loop_image(void *param);
int		close_cross(t_data *data);

t_data  *check_error_arg(int argc, char **argv);

t_3vecf	ray_trace(t_3vecf orig, t_3vecf dir, float min_dist, float max_dist, t_data *data);
t_obj	*ray_first_intersect(t_3vecf orig, t_3vecf dir, float min_dist, float max_dist, float *closest_dist, t_obj *objs);

float	compute_lights(t_3vecf inter_point, t_3vecf normal_inter, t_3vecf inv_dir, t_light *lights, t_obj *objs);

int     solve_quadra(t_polynome p, float *dist, float min_dist, float max_dist);
int		return_update(char *error, int ret);

int		syntax_plane(char *line, int i, t_plane *p, t_3vecf *color);
int		syntax_cone(char *line, int i, t_cone *c, t_3vecf *color);
int		syntax_cylinder(char *line, int i, t_cylinder *c, t_3vecf *color);
int		syntax_sphere(char *line, int i, t_sphere *s, t_3vecf *color);

#endif
