/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 21:44:26 by hnam              #+#    #+#             */
/*   Updated: 2019/04/16 22:27:56 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls(t_ls ls, char *name, int root_show)
{
	DIR				*d;
	struct dirent	*p;
	t_dp			*dp;
	int				dp_exist;

	dp_exist = 0;
	if ((d = opendir(name)))
	{
		root_show ? ft_printf("%s: \n", name) : 0;
		while ((p = readdir(d)))
		{
			if (!IS_SAME(ls.flag, a_FLAG) && IS_HIDDEN(p->d_name))
				continue;
			make_linked_data(p, &dp, dp_exist++, name, ls);
		}
		dp_exist ? sort_dp(&dp, ls) : 0;
		dp_exist ? display_dp(dp, ls) : ft_printf("\n");
		while (dp_exist && IS_SAME(ls.flag, R_FLAG) && dp)
		{
			if (dp->type == DT_DIR && !is_hidden(dp->name) && dp->curr)
				ft_ls(ls, dp->curr, 1);
			if (!dp->next)
				break;
			dp = dp->next;
		}
		dp_exist ? free_dp(dp) : 0;
	}
}

int		main(int ac, char *av[])
{
	int		f_count;
	int		i;
	t_ls	ls;
	t_fi	*tmp;

	f_count = 0;
	i = 1;
	while (ac > 1 && ft_start_with(av[i], '-') && ft_strlen(av[i]) != 1)
		ls.flag = get_ls_flag(&av[i++][1], &ac);
	while (ac > 1 && av[i])
		make_linked_fi(av[i++], &ls, &f_count);
	if (f_count)
	{
		fi_set_to_head(&ls.fi);
		sort_fi(&ls.fi);
		while (ls.fi)
		{
			tmp = ls.fi;
			ft_ls(ls, ls.fi->name, (f_count > 1 || ac - f_count > 1) ? 1 : 0);
			ls.fi = ls.fi->next;
			free(tmp);
		}
	}
	(ac == 1) ? ft_ls(ls, ".", 0) : 0;
	// while (1)
	// 	sleep(1);
	return (0);
}
