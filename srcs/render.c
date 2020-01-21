/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/21 22:42:45 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/21 04:42:54 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

t_3vecf	window_to_view(int x, int y)
{
	t_3vecf	vec;
	
	vec.val[0] = (float)x / (float)WIN_WIDTH;
	vec.val[1] = (float)y / (float)WIN_HEIGHT;
	if (WIN_WIDTH > WIN_HEIGHT)
		vec.val[0] *= (float)WIN_WIDTH / (float)WIN_HEIGHT;
	else if (WIN_HEIGHT > WIN_WIDTH)
		vec.val[1] *= (float)WIN_HEIGHT / (float)WIN_WIDTH;
	vec.val[2] = 1;
	return (vec);
}

float	compute_lights(t_3vecf inter_point, t_3vecf normal_inter, t_3vecf inv_dir, t_light *lights, t_obj *objs)
{
	float	light_fact;
	float	norm_dot_ldir;
	float	ref_dot_idir;
	float	shadow_dist;
	float	light_len;
	t_3vecf	light_dir;
	t_3vecf	spec_vec;
	t_obj	*shadow_obj;

	light_fact = 0.f;
	while (lights)
	{
		if (lights->light_type == LIGHT_AMBIENT)
			light_fact += lights->intensity;
		else
		{
			if (lights->light_type == LIGHT_POINT)
			{
				light_dir = sub_3vecf(lights->origin, inter_point);
				light_len = get_length_3vecf(light_dir);
			}
			else if (lights->light_type == LIGHT_DIRECTIONAL)
			{
				light_dir = invert_3vecf(lights->origin);
				light_len = FLT_MAX;
			}
			normalize_3vecf(&light_dir);
			shadow_obj = ray_first_intersect(inter_point, light_dir, 0.01, light_len, &shadow_dist, objs);
			if (!shadow_obj)
			{
				norm_dot_ldir = dot_product_3vecf(normal_inter, light_dir);
				if (norm_dot_ldir > 0)
					light_fact += lights->intensity * norm_dot_ldir / (get_length_3vecf(normal_inter) * get_length_3vecf(light_dir));
				spec_vec.val[0] = 2 * normal_inter.val[0] * norm_dot_ldir - light_dir.val[0];
				spec_vec.val[1] = 2 * normal_inter.val[1] * norm_dot_ldir - light_dir.val[1];
				spec_vec.val[2] = 2 * normal_inter.val[2] * norm_dot_ldir - light_dir.val[2];
				ref_dot_idir = dot_product_3vecf(spec_vec, inv_dir);
				if (ref_dot_idir > 0)
					light_fact += lights->intensity * powf(ref_dot_idir / (get_length_3vecf(spec_vec) * get_length_3vecf(inv_dir)), 100);
			}
		}
		lights = lights->next;
	}
	return (light_fact);
}

int		clip_color(float color)
{
	if (color > 255)
		return (255);
	else if (color < 0)
		return (0);
	else
		return ((int)color);
}

void	ray_put_pixel(int i, int j, int *img, t_3vecf color)
{
	int		rgb_color;

	i = WIN_WIDTH / 2 + i;
	j = WIN_HEIGHT / 2 + j;
	rgb_color = (clip_color(color.val[0] * 255) << 16);
	rgb_color |= (clip_color(color.val[1] * 255) << 8);
	rgb_color |= clip_color(color.val[2] * 255);
	img[j * WIN_WIDTH + i] = rgb_color;
}

void	*render_thread(void *param)
{
	t_3vecf	orig;
	t_3vecf	dir;
	t_3vecf	color;
	int		i;
	int		j;
	t_thread	*thread = (t_thread *)param;
	t_data	*data = thread->data;

	i = thread->start;
	orig = data->camera->origin;
	while (i < thread->end)
	{
		j = -WIN_HEIGHT / 2;
		while (j < WIN_HEIGHT / 2)
		{
			dir = mult_3vecf_33matf(mult_3vecf_33matf(window_to_view(i, j), data->rot_mat[1]), data->rot_mat[0]);
			color = ray_trace(orig, dir, 0.01, FLT_MAX, data);
			ray_put_pixel(i, j, data->mlx->img_str, color);
			++j;
		}
		++i;
	}
	pthread_exit(NULL);
	return (NULL);
}

void	render(t_data *data)
{
	int		ret;
	int		i;
	t_thread	threads_param[NB_THREADS];
	pthread_t	threads[NB_THREADS];

	init_threads(threads_param, data);
	t_3vecf tm = mult_3vecf_33matf(assign_3vecf(1, 0, 0), data->rot_mat[1]);
	data->rot_mat[0] = init_rotation_matrix_vec(tm, degree_to_radian(data->camera->rotation.val[0]));	
	i = 0;
	while (i < NB_THREADS)
	{
		ret = pthread_create(&(threads[i]), NULL, render_thread, (void *)(&(threads_param[i])));
		if (ret)
			exit(EXIT_FAILURE);
		++i;
	}
	i = 0;
	while (i < NB_THREADS)
		pthread_join(threads[i++], NULL);
}
