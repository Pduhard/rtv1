/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key_hook.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aplat <aplat@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/30 20:52:29 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 11:52:19 by aplat       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "rtv1.h"

int		close_cross(t_data *data)
{
	free_all(data);
	exit(0);
	return (0);
}

int		key_press(int keycode, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (keycode == ESC_KEY)
	{
		free_all(data);
		exit(0);
	}
	if (keycode == 0)
		data->hooks |= A_KEY;
	else if (keycode == 1)
		data->hooks |= S_KEY;
	else if (keycode == 2)
		data->hooks |= D_KEY;
	else if (keycode == 13)
		data->hooks |= W_KEY;
	else if (keycode == 3)
		data->hooks |= F_KEY;
	else
		return (key_press2(keycode, data));
	return (1);
}

int		key_press2(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 5)
		data->hooks |= G_KEY;
	else if (keycode == 123)
		data->hooks |= ARR_LEFT_KEY;
	else if (keycode == 124)
		data->hooks |= ARR_RIGHT_KEY;
	else if (keycode == 125)
		data->hooks |= ARR_DOWN_KEY;
	else if (keycode == 126)
		data->hooks |= ARR_UP_KEY;
	else if (keycode == 49)
		data->hooks |= SPACE_KEY;
	else if (keycode == 257)
		data->hooks |= SHIFT_KEY;
	return (1);
}

int		key_release(int keycode, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (keycode == 0)
		data->hooks -= A_KEY;
	else if (keycode == 1)
		data->hooks -= S_KEY;
	else if (keycode == 2)
		data->hooks -= D_KEY;
	else if (keycode == 13)
		data->hooks -= W_KEY;
	else if (keycode == 3)
		data->hooks -= F_KEY;
	else
		return (key_release2(keycode, data));
	return (1);
}

int		key_release2(int keycode, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (keycode == 5)
		data->hooks -= G_KEY;
	else if (keycode == 123)
		data->hooks -= ARR_LEFT_KEY;
	else if (keycode == 124)
		data->hooks -= ARR_RIGHT_KEY;
	else if (keycode == 125)
		data->hooks -= ARR_DOWN_KEY;
	else if (keycode == 126)
		data->hooks -= ARR_UP_KEY;
	else if (keycode == 49)
		data->hooks -= SPACE_KEY;
	else if (keycode == 257)
		data->hooks -= SHIFT_KEY;
	return (1);
}
