/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:19:09 by hnam              #+#    #+#             */
/*   Updated: 2019/04/14 23:56:36 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flags c_to_b_flag[] =
{
	{'1', one_FLAG},
	{'l', l_FLAG},
	{'a', a_FLAG},
	{'r', r_FLAG},
	{'R', R_FLAG},
	{'t', t_FLAG},
	{'S', S_FLAG},
	{0, 0},
};

int get_ls_flag(char *flags, int *counter)
{
	int	flag;
	int	i;

	flag = 0;
	while (*flags)
	{
		if (ft_strchr(VALID_FLAG, *flags) == NULL)
			error_exit(INVALID_FLAG, flags);
		i = -1;
		while (++i < NUM_OF_FLAG)
		{
			if (c_to_b_flag[i].flag == *flags)
			{
				flag = flag | c_to_b_flag[i].bin_flag;
			}
		}
		flags++;
	}
	*counter -= 1;
	return flag;
}
