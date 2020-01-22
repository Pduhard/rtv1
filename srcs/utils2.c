/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/22 10:09:52 by aplat        #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 11:29:07 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

int		determine_light(char *line, t_light *l)
{
	int	i;

	i = 5;
	while (ft_isspace(line[i]))
		++i;
	if (line[i++] != '(')
		return (return_update(SERRORLIGHT, 0));
	if (!ft_strncmp(&(line[i]), "point", 5))
	{
		l->light_type = LIGHT_POINT;
		i += 5;
	}
	else if (!ft_strncmp(&(line[i]), "ambient", 7))
	{
		l->light_type = LIGHT_AMBIENT;
		i += 7;
	}
	else if (!ft_strncmp(&(line[i]), "directional", 11))
	{
		l->light_type = LIGHT_DIRECTIONAL;
		i += 11;
	}
	else
		return (return_update(SERRORLIGHT, 0));
	return (i);
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

float	set_light_dir(t_3vecf *light_dir, t_light *lights, t_3vecf inter_point)
{
	float	light_len;

	light_len = 0.f;
	if (lights->light_type == LIGHT_POINT)
	{
		*light_dir = sub_3vecf(lights->origin, inter_point);
		light_len = get_length_3vecf(*light_dir);
	}
	else if (lights->light_type == LIGHT_DIRECTIONAL)
	{
		*light_dir = invert_3vecf(lights->origin);
		light_len = FLT_MAX;
	}
	return (light_len);
}

float	add_light_intensity(t_3vecf l_dir, t_3vecf normal_inter,
	t_3vecf inv_dir, t_light *lights)
{
	float	norm_dot_ldir;
	float	ref_dot_idir;
	t_3vecf	spec_vec;
	float	light_fact;

	light_fact = 0.f;
	norm_dot_ldir = dot_product_3vecf(normal_inter, l_dir);
	if (norm_dot_ldir > 0)
		light_fact += lights->intensity * norm_dot_ldir
			/ (get_length_3vecf(normal_inter) * get_length_3vecf(l_dir));
	spec_vec.val[0] = 2 * normal_inter.val[0] * norm_dot_ldir - l_dir.val[0];
	spec_vec.val[1] = 2 * normal_inter.val[1] * norm_dot_ldir - l_dir.val[1];
	spec_vec.val[2] = 2 * normal_inter.val[2] * norm_dot_ldir - l_dir.val[2];
	ref_dot_idir = dot_product_3vecf(spec_vec, inv_dir);
	if (ref_dot_idir > 0)
		light_fact += lights->intensity * powf(ref_dot_idir
			/ (get_length_3vecf(spec_vec) * get_length_3vecf(inv_dir)), 100);
	return (light_fact);
}
