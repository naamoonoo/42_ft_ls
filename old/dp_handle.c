#include "ft_ls.h"

void	handle_dp_data(DIR *dirp, t_ls ls)
{
	int 			i;
	t_dp			*dp;
	struct dirent	*p;
	// DIR				*d;

	i = 0;
	while ((p = readdir(dirp)) != NULL)
	{
		printf("%s\n", p->d_name);
		if (!is_dot(p->d_name) && p->d_type == DT_DIR)
		{
			printf("%s is folder\n", p->d_name);
			// printf("%s will be returned\n", readdir(d)->d_name);
			handle_dp_data(opendir(ft_strjoin("lib/",p->d_name)), ls);
		}
		link_dp(&dp, p);
		// get data and linked it!
			// if directory found -> call handle_dp_data(opendir(dp.d_name), ls);
	}
	sort_dp(&dp, ls);
	display_dp(dp, ls);
		// sorting it by ls flag!

		// print it by ls flag!!
}

void	link_dp(t_dp **dp, struct dirent *p)
{
	static int	counter = 0;
	struct stat	info;
	t_dp		*temp;

	temp = malloc(sizeof(t_dp));
	temp->p = p;
	temp->name = p->d_name;
	lstat(temp->name, &info);
	temp->info = info;
	temp->next = NULL;
	temp->prev = NULL;
	if (counter++ != 0)
	{
		temp->prev = (*dp);
		(*dp)->next = temp;
	}
	(*dp) = temp;
}
// void	sorting_dp()


void	sort_dp(t_dp **dp, t_ls ls)
{
	int			len;

	dp_set_to_head(dp);
	len = get_dp_len(*dp);
	while (len-- > 0)
	{
		while ((*dp)->next)
		{
			// printf("is r? %d\n", IS_r_FLAG(ls.flag));
			if (IS_r_FLAG(ls.flag) ?
				ft_strcmp((*dp)->name, (*dp)->next->name) < 0 :
				ft_strcmp((*dp)->name, (*dp)->next->name) > 0)
				swap_dp(dp);
			// else if (!IS_r_FLAG(ls.flag) && ft_strcmp((*dp)->name, (*dp)->next->name) > 0)
			// 	swap_dp(dp);
			(*dp) = (*dp)->next;
		}
		dp_set_to_head(dp);
	}
}

void	swap_dp(t_dp **dp)
{
	struct dirent	*t_p;
	struct stat		t_info;
	char			*t_name;

	t_p = (*dp)->next->p;
	t_info = (*dp)->next->info;
	t_name = (*dp)->next->name;
	(*dp)->next->p = (*dp)->p;
	(*dp)->next->info = (*dp)->info;
	(*dp)->next->name = (*dp)->name;
	(*dp)->p = t_p;
	(*dp)->info = t_info;
	(*dp)->name = t_name;
}

void	display_dp(t_dp *dp, t_ls ls)
{
	// struct dirent	*dp;
	t_dp			*temp;
	while (dp)
	{
		temp = dp;
		// printf("%s\n", dp->p->d_name);

		ft_start_with(dp->p->d_name, '.') ? 0 :
		printf("%s%c", dp->p->d_name, IS_one_FLAG(ls.flag) ? '\n' : '\t');
		// printf("\n\n");
		dp = dp->next;
		free(temp);
	}
}
