#include "ft_ls.h"

int	main(int ac, char *av[])
{
	int		f_count;
	int		i;
	t_ls	ls;

	f_count = 0;
	i = 1;
	while (ac > 1 && i < ac && ft_start_with(av[i], '-'))
		ls.flag = get_ls_flag(&av[i++][1], &ac);
	while (ac > 1 && av[i])
		make_linked_fi(av[i++], &ls, &f_count);
	if (f_count)
	{
		fi_set_to_head(&ls.fi);
		sort_fi(&ls.fi);
		while (ls.fi)
		{
			ft_ls(ls, ls.fi->name, (f_count > 1 || ac - f_count > 1) ? 1 : 0);
			ls.fi = ls.fi->next;
		}
		// free(ls.fi)
	}
	(ac == 1) ? ft_ls(ls, ".", 0) : 0;
	return (0);
}

void	make_linked_fi(char *name, t_ls *ls, int *f_count)
{
	static int	count = 0;
	t_fi		*temp;
	struct stat	info;

	if (opendir(name) == NULL && lstat(name, &info) != 0)
	{
		error_alert(INVALID_INPUT, name);
		return ;
	}
	temp = malloc(sizeof(t_fi));
	temp->name = name;
	temp->next = NULL;
	temp->prev = NULL;
	if (count++ != 0)
	{
		temp->prev = ls->fi;
		ls->fi->next = temp;
	}
	ls->fi = temp;
	*f_count += 1;
}

void	ft_ls(t_ls ls, char *name, int root_show)
{
	DIR				*d;
	struct dirent	*p;
	t_dp			*dp;
	int				dp_exist;

	dp_exist = 0;
	if ((d = opendir(name)))
	{
		root_show ? printf("%s: \n", name) : 0;
		while ((p = readdir(d)))
		{
			if (!IS_a_FLAG(ls.flag) && IS_HIDDEN(p->d_name))
				continue;
			make_linked_data(p, &dp, dp_exist++, name);
		}
		dp_exist ? sort_dp(&dp, &ls) : 0;
		dp_exist ? display_dp(dp, ls) : ft_printf("\n");
		while (dp_exist && IS_R_FLAG(ls.flag) && dp)
		{
			if (dp->type == DT_DIR && !is_hidden(dp->name) && dp->curr)
				ft_ls(ls, dp->curr, 1);
			dp = dp->next;
			//free dp
		}
	}
}

void	make_linked_data(struct dirent *p, t_dp **dp, int dp_exist, char *name)
{
	t_dp		*temp;
	struct stat	info;

	temp = malloc(sizeof(t_dp));
	temp->name = p->d_name;
	temp->type = p->d_type;
	if (!is_hidden(temp->name))
		temp->curr = ft_strjoin_by(name, p->d_name, '/');
	else
		temp->curr = NULL;
	lstat(temp->curr, &info);
	// nameing printing with color depend on info!
	temp->info = info;
	temp->next = NULL;
	temp->prev = NULL;
	if (dp_exist != 0)
	{
		temp->prev = (*dp);
		(*dp)->next = temp;
	}
	(*dp) = temp;
}

void	sort_dp(t_dp **dp, t_ls *ls)
{
	int	times;

	ls->len = (int)ft_strlen((*dp)->name);
	dp_set_to_head(dp);
	times = get_dp_len(*dp);
	while (times-- > 0)
	{
		while ((*dp)->next)
		{
			if (IS_r_FLAG(ls->flag) ?
				ft_strcmp((*dp)->name, (*dp)->next->name) < 0 :
				ft_strcmp((*dp)->name, (*dp)->next->name) > 0)
				swap_dp(dp);
			// else if (IS_s_FLAG(ls.flag) && IS_r_FLAG(ls.flag) ?
			// 	ft_strcmp((*dp)->name, (*dp)->next->name) < 0 :
			// 	ft_strcmp((*dp)->name, (*dp)->next->name) > 0)
			// 	swap_dp(dp);
			// else if (!IS_r_FLAG(ls.flag) && ft_strcmp((*dp)->name, (*dp)->next->name) > 0)
			// 	swap_dp(dp);
			ls->len = get_big((int)ft_strlen((*dp)->name), ls->len);
			(*dp) = (*dp)->next;
		}
		dp_set_to_head(dp);
	}
	dp_set_to_head(dp);
}


void	display_dp(t_dp *dp, t_ls ls)
{
	char	*temp;

	while (dp)
	{
		temp = ft_strsub(ctime(&(dp->info.st_mtime)), 4, 12);
		IS_l_FLAG(ls.flag) ?
		ft_printf("%s\t%d\t%s\t%s\t%d\t%s\t%s\n",
			ft_itoa_base(dp->info.st_mode, 2 ,0),
			dp->info.st_nlink,
			getpwuid(dp->info.st_uid)->pw_name,
			getgrgid(dp->info.st_gid)->gr_name,
			dp->info.st_size,
			temp,
			dp->name
			) :
		ft_printf("%-*s", ls.len + 1, dp->name);
		free(temp);
		dp = dp->next;
	}
	ft_printf("\n\n");
}

void	swap_dp(t_dp **dp)
{
	char		*t_name;
	char		*t_curr;
	struct stat	t_info;
	int			t_type;

	t_name = (*dp)->next->name;
	t_type = (*dp)->next->type;
	t_curr = (*dp)->next->curr;
	t_info = (*dp)->next->info;
	(*dp)->next->name = (*dp)->name;
	(*dp)->next->type = (*dp)->type;
	(*dp)->next->curr = (*dp)->curr;
	(*dp)->next->info = (*dp)->info;
	(*dp)->name = t_name;
	(*dp)->type = t_type;
	(*dp)->curr = t_curr;
	(*dp)->info = t_info;
}
// ft_atoi.c        	ft_atoi_base.c
// ft_atoi.c             ft_memccpy.c
// ft_atoi.o        ft_atoi_base.ol
// ft_atoi.c             ft_memccpy.c
