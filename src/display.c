/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 21:43:03 by hnam              #+#    #+#             */
/*   Updated: 2019/04/16 22:18:51 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_dp(t_dp *dp, t_ls ls)
{
	long long int	blocks;

	blocks = 0;
	dp_set_to_head(&dp);
	while (IS_SAME(ls.flag, l_FLAG) && dp)
	{
		blocks += dp->info.st_blocks;
		if (!dp->next)
			break;
		dp = dp->next;
	}
	dp_set_to_head(&dp);
	IS_SAME(ls.flag, l_FLAG) ? ft_printf("total %lld\n", blocks) : 0;
	while (dp)
	{
		if (IS_SAME(ls.flag, l_FLAG))
			display_l_form(dp, ls);
		else
			display_name(dp, ls);
		if (!dp->next)
			break;
		dp = dp->next;
	}
	if (!IS_SAME(ls.flag, l_FLAG) && !IS_SAME(ls.flag, one_FLAG))
		ft_printf("\n");
}

void	display_l_form(t_dp *dp, t_ls ls)
{
	char	*t;
	char	*buf;
	char	*mode;


	t = ft_strsub(ctime(&(dp->time_)), 4, 12);
	mode = get_mode(dp->info.st_mode);
	buf = ft_memalloc(dp->info.st_size + 1);
	if (ft_start_with(mode, 'l'))
		readlink(dp->curr, buf, dp->info.st_size + 1);
	else
		buf = NULL;
	ft_printf("%s %2d %-5s%6s %6d %s ",
	mode, dp->info.st_nlink, getpwuid(dp->info.st_uid)->pw_name,
	getgrgid(dp->info.st_gid)->gr_name, dp->info.st_size,
	IS_SAME(ls.flag, T_FLAG) ? ctime(&(dp->time_)) : t);
	display_name(dp, ls);
	ft_start_with(mode, 'l') ? ft_printf(" -> %s\n", buf) : ft_printf("\n");
	!dp->next ? ft_printf("\n") : 0;
	free(t);
	free(mode);
	free(buf);
}

void	display_name(t_dp *dp, t_ls ls)
{
	if (IS_SAME(ls.flag, l_FLAG))
	{
		IS_SAME(ls.flag, G_FLAG) ?
			colored_print(dp->name, dp->info.st_mode) :
			ft_printf("%s", dp->name);
	}
	else
	{
		IS_SAME(ls.flag, G_FLAG) ?
			colored_print(dp->name, dp->info.st_mode) :
			ft_printf("%s", dp->name);
		ft_printf("%c", IS_SAME(ls.flag, one_FLAG) ? '\n' : '\t');
		!dp->next ? ft_printf("\n") : 0;
	}
}

void	colored_print(char *name, int mode)
{
	char *temp;

	temp = get_mode(mode);
	if (temp[0] == 'd')
		ft_printf("{blue}%s{eoc}", name);
	else if (temp[0] == 'l')
		ft_printf("{magenta}%s{eoc}", name);
	else if (ft_strchr(temp, 'x'))
		ft_printf("{red}%s{eoc}", name);
	else
		ft_printf("%s", name);
	free(temp);
}

char	*get_mode(int mode)
{
	char	*res;

	res = ft_memalloc(11);
	S_ISBLK(mode) ? (res[0] = 'b') : 0;
	S_ISCHR(mode) ? (res[0] = 'c') : 0;
	S_ISDIR(mode) ? (res[0] = 'd') : 0;
	S_ISFIFO(mode) ? (res[0] = 'p') : 0;
	S_ISREG(mode) ? (res[0] = '-') : 0;
	S_ISLNK(mode) ? (res[0] = 'l') : 0;
	S_ISSOCK(mode) ? (res[0] = 's') : 0;
	res[1] = IS_SAME(mode, S_IRUSR) ? 'r' : '-';
	res[2] = IS_SAME(mode, S_IWUSR) ? 'w' : '-';
	res[3] = IS_SAME(mode, S_IXUSR) ? 'x' : '-';
	res[4] = IS_SAME(mode, S_IRGRP) ? 'r' : '-';
	res[5] = IS_SAME(mode, S_IWGRP) ? 'w' : '-';
	res[6] = IS_SAME(mode, S_IXGRP) ? 'x' : '-';
	res[7] = IS_SAME(mode, S_IROTH) ? 'r' : '-';
	res[8] = IS_SAME(mode, S_IWOTH) ? 'w' : '-';
	res[9] = IS_SAME(mode, S_IXOTH) ? 'x' : '-';
	res[10] = '\0';
	return (res);
}
