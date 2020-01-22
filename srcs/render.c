/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/21 22:42:45 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 14:51:17 by aplat       ###    #+. /#+    ###.fr     */
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

float	compute_lights(t_3vecf inter_point, t_3vecf normal_inter,
	t_3vecf inv_dir, t_to_loop t_loop)
{
	t_dist	dist;
	float	light_fact;
	float	shadow_dist;
	t_3vecf	light_dir;
	t_obj	*shadow_obj;

	light_fact = 0.f;
	while (t_loop.lights)
	{
		if (t_loop.lights->light_type == LIGHT_AMBIENT)
			light_fact += t_loop.lights->intensity;
		else
		{
			dist = (t_dist){&shadow_dist, 0.01, set_light_dir(&light_dir,
				t_loop.lights, inter_point)};
			normalize_3vecf(&light_dir);
			if (!(shadow_obj = ray_first_intersect(inter_point,
				light_dir, dist, t_loop.objs)))
				light_fact += add_light_intensity(light_dir,
					normal_inter, inv_dir, t_loop.lights);
		}
		t_loop.lights = t_loop.lights->next;
	}
	return (light_fact);
}

void	*render_thread(void *param)
{
	t_3vecf		orig;
	t_3vecf		dir;
	t_3vecf		color;
	t_thread	*thread;
	t_data		*data;

	thread = (t_thread *)param;
	data = thread->data;
	thread->i = thread->start;
	orig = data->camera->origin;
	while (thread->i < thread->end)
	{
		thread->j = -WIN_HEIGHT / 2;
		while (thread->j < WIN_HEIGHT / 2)
		{
			dir = mult_3vecf_33matf(mult_3vecf_33matf(window_to_view(thread->i,
				thread->j), data->rot_mat[1]), data->rot_mat[0]);
			color = ray_trace(orig, dir, (t_dist){NULL, 0.01, FLT_MAX}, data);
			ray_put_pixel(thread->i, thread->j, data->mlx->img_str, color);
			++thread->j;
		}
		++thread->i;
	}
	pthread_exit(NULL);
	return (NULL);
}

void	render(t_data *data)
{
	int			ret;
	int			i;
	t_3vecf		tm;
	t_thread	threads_param[NB_THREADS];
	pthread_t	threads[NB_THREADS];

	init_threads(threads_param, data);
	tm = mult_3vecf_33matf(assign_3vecf(1, 0, 0), data->rot_mat[1]);
	data->rot_mat[0] = init_rotation_matrix_vec(tm,
		degree_to_radian(data->camera->rotation.val[0]));
	i = 0;
	while (i < NB_THREADS)
	{
		ret = pthread_create(&(threads[i]), NULL,
			render_thread, (void *)(&(threads_param[i])));
		if (ret)
			exit(EXIT_FAILURE);
		++i;
	}
	i = 0;
	while (i < NB_THREADS)
		pthread_join(threads[i++], NULL);
}
