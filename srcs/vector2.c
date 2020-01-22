/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vector2.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/22 08:00:22 by aplat        #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 09:07:20 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

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

t_3vecf	productadd_3vecf(t_3vecf a, t_3vecf b, float c)
{
	t_3vecf	vec;

	vec.val[0] = a.val[0] + b.val[0] * c;
	vec.val[1] = a.val[1] + b.val[1] * c;
	vec.val[2] = a.val[2] + b.val[2] * c;
	return (vec);
}

t_3vecf	productwf_3vecf(t_3vecf a, float b)
{
	t_3vecf	vec;

	vec.val[0] = a.val[0] * b;
	vec.val[1] = a.val[1] * b;
	vec.val[2] = a.val[2] * b;
	return (vec);
}

t_3vecf	add_3vecf(t_3vecf a, t_3vecf b)
{
	t_3vecf	vec;

	vec.val[0] = a.val[0] + b.val[0];
	vec.val[1] = a.val[1] + b.val[1];
	vec.val[2] = a.val[2] + b.val[2];
	return (vec);
}
