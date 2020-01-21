/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vector.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/21 23:02:40 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/21 05:00:09 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

t_3vecf	invert_3vecf(t_3vecf vec)
{
	return (assign_3vecf(-vec.val[0], -vec.val[1], -vec.val[2]));
}

float	dot_product_3vecf(t_3vecf a, t_3vecf b)
{
	return (a.val[0] * b.val[0] + a.val[1] * b.val[1] + a.val[2] * b.val[2]);
}

float	get_length_3vecf(t_3vecf vec)
{
	return (sqrtf(dot_product_3vecf(vec, vec)));
}

void	normalize_3vecf(t_3vecf *vec)
{
	float	length;

	length = get_length_3vecf(*vec);
	vec->val[0] = vec->val[0] / length;
	vec->val[1] = vec->val[1] / length;
	vec->val[2] = vec->val[2] / length;
}

t_3vecf	sub_3vecf(t_3vecf a, t_3vecf b)
{
	t_3vecf	vec;

	vec.val[0] = a.val[0] - b.val[0];
	vec.val[1] = a.val[1] - b.val[1];
	vec.val[2] = a.val[2] - b.val[2];
	return (vec);
}

t_3vecf	assign_3vecf(float x, float y, float z)
{
	t_3vecf	vec;

	vec.val[0] = x;
	vec.val[1] = y;
	vec.val[2] = z;
	return (vec);
}

t_3vecf	product_3vecf(t_3vecf a, t_3vecf b)
{
	t_3vecf	vec;

	vec.val[0] = (a.val[1] * b.val[2] - a.val[2] * b.val[1]);
	vec.val[1] = (a.val[2] * b.val[0] - a.val[0] * b.val[2]);
	vec.val[2] = (a.val[0] * b.val[1] - a.val[1] * b.val[0]);
	return (vec);
}

t_3vecf productadd_3vecf(t_3vecf a, t_3vecf b, float c)
{
	t_3vecf	vec;

	vec.val[0] = a.val[0] + b.val[0] * c;
	vec.val[1] = a.val[1] + b.val[1] * c;
	vec.val[2] = a.val[2] + b.val[2] * c;
	return (vec);
}

t_3vecf productwf_3vecf(t_3vecf a, float b)
{
	t_3vecf	vec;

	vec.val[0] = a.val[0] * b;
	vec.val[1] = a.val[1] * b;
	vec.val[2] = a.val[2] * b;
	return (vec);
}