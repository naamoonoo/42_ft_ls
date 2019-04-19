/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 21:38:08 by hnam              #+#    #+#             */
/*   Updated: 2019/04/16 23:50:26 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	swap_fi(t_fi **fi)
{
	char		*t_name;

	t_name = (*fi)->next->name;
	(*fi)->next->name = (*fi)->name;
	(*fi)->name = t_name;
}

void	sort_fi(t_fi **fi)
{
	int	len;

	len = get_fi_len(*fi);
	while (len-- > 0)
	{
		while ((*fi)->next)
		{
			if (ft_strcmp((*fi)->name, (*fi)->next->name) > 0)
				swap_fi(fi);
			(*fi) = (*fi)->next;
		}
		fi_set_to_head(fi);
	}
	fi_set_to_head(fi);
}

void	sort_dp(t_dp **dp, t_ls ls, char *name, int root_show)
{
	int	times;

	root_show ? ft_printf("%s: \n", name) : 0;
	dp_set_to_head(dp);
	times = get_dp_len(*dp);
	while (times-- > 0)
	{
		while ((*dp)->next)
		{
			sort_by_flag(dp, ls);
			(*dp) = (*dp)->next;
		}
		dp_set_to_head(dp);
	}
}

void	sort_by_flag(t_dp **dp, t_ls ls)
{
	if (IS_SAME(ls.flag, S_FLAG))
	{
		if (IS_SAME(ls.flag, r_FLAG) ?
			(*dp)->info.st_size > (*dp)->next->info.st_size :
			(*dp)->info.st_size < (*dp)->next->info.st_size)
			swap_dp(dp);
	}
	else if (IS_SAME(ls.flag, t_FLAG))
	{
		if (IS_SAME(ls.flag, r_FLAG) ?
			(*dp)->time_ > (*dp)->next->time_ :
			(*dp)->time_ < (*dp)->next->time_)
			swap_dp(dp);
	}
	else
	{
		if (IS_SAME(ls.flag, r_FLAG) ?
			ft_strcmp((*dp)->name, (*dp)->next->name) < 0 :
			ft_strcmp((*dp)->name, (*dp)->next->name) > 0)
			swap_dp(dp);
	}
}

void	swap_dp(t_dp **dp)
{
	char		*t_name;
	char		*t_curr;
	struct stat	t_info;
	int			t_type;
	long int	t_time_;

	t_name = (*dp)->next->name;
	t_type = (*dp)->next->type;
	t_curr = (*dp)->next->curr;
	t_info = (*dp)->next->info;
	t_time_ = (*dp)->next->time_;
	(*dp)->next->name = (*dp)->name;
	(*dp)->next->type = (*dp)->type;
	(*dp)->next->curr = (*dp)->curr;
	(*dp)->next->info = (*dp)->info;
	(*dp)->next->time_ = (*dp)->time_;
	(*dp)->name = t_name;
	(*dp)->type = t_type;
	(*dp)->curr = t_curr;
	(*dp)->info = t_info;
	(*dp)->time_ = t_time_;
}
