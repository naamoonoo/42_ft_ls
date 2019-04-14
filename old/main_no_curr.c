#include "ft_ls.h"

int	main(int ac, char *av[])
{
	int 	file_exist;
	int		i;
	t_ls	ls;

	file_exist = 0;
	i = 1;
	while (ac > 1 && i < ac && ft_start_with(av[i], '-'))
		ls.flag = get_ls_flag(&av[i++][1]);
	while (ac > 1 && i < ac)
		make_linked_fi(av[i++], &ls, &file_exist);
	if (file_exist)
	{
		fi_set_to_head(&ls.fi);
		sort_fi(&ls.fi);
		while (ls.fi)
		{
			ft_ls(ls, ls.fi->name, 0);
			ls.fi = ls.fi->next;
		}
	}
	else
		ft_ls(ls, ".", 0);
	return (0);
}

void	make_linked_fi(char *name, t_ls *ls, int *file_exist)
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
	*file_exist += 1;
}

void	ft_ls(t_ls ls, char *name, int is_root)
{
	DIR				*d;
	struct dirent	*p;
	t_dp			*dp;
	int				start;
	// char			*tmp;

	start = 0;
	is_root ? printf("%s: \n", name) : 0;
	if ((d = opendir(name)))
	{
		while ((p = readdir(d)))
		{
			make_linked_data(p, &dp, start++);
		}
		sort_dp(&dp, ls);
		display_dp(dp, ls);
		while (dp)
		{
			if (dp->type == DT_DIR && !IS_HIDDEN(dp->name))
			{
				dp->curr = ft_strjoin_by(name, dp->name, '/');
				ft_ls(ls, dp->curr, 1);
				free(dp->curr);
			}
			dp = dp->next;
		}
		//freeing
	}
	else
	{
		//len control need ls
		printf("%s\n" name);
	}


}

void	make_linked_data(struct dirent *p, t_dp **dp, int start)
{
	t_dp		*temp;

	temp = malloc(sizeof(t_dp));
	temp->name = p->d_name;
	temp->type = p->d_type;
	temp->next = NULL;
	temp->prev = NULL;
	if (start != 0)
	{
		temp->prev = (*dp);
		(*dp)->next = temp;
	}
	(*dp) = temp;
}

void	sort_dp(t_dp **dp, t_ls ls)
{
	int	times;

	dp_set_to_head(dp);
	times = get_dp_len(*dp);
	while (times-- > 0)
	{
		while ((*dp)->next)
		{
			if (IS_r_FLAG(ls.flag) ?
				ft_strcmp((*dp)->name, (*dp)->next->name) < 0 :
				ft_strcmp((*dp)->name, (*dp)->next->name) > 0)
				swap_dp(dp);
			// else if (IS_s_FLAG(ls.flag) && IS_r_FLAG(ls.flag) ?
			// 	ft_strcmp((*dp)->name, (*dp)->next->name) < 0 :
			// 	ft_strcmp((*dp)->name, (*dp)->next->name) > 0)
			// 	swap_dp(dp);
			// else if (!IS_r_FLAG(ls.flag) && ft_strcmp((*dp)->name, (*dp)->next->name) > 0)
			// 	swap_dp(dp);
			ls.len = get_big((int)ft_strlen((*dp)->name), ls.len);
			(*dp) = (*dp)->next;
		}
		dp_set_to_head(dp);
	}
	dp_set_to_head(dp);
}


void	display_dp(t_dp *dp, t_ls ls)
{
	// char			*tmp;
	struct stat		info;

	// ls.curr = ft_strjoin(name, "/");
	// if (IS_DIR(dp->name))
	// {
	// while (IS_HIDDEN(dp->name))
	// 	dp = dp->next;
	ls.len +=1;
	// printf("%s: \n", dp->name);
	while (dp)
	{
		lstat(dp->name, &info);
		// // if (!IS_a_FLAG(ls.flag) &&
		if(IS_HIDDEN(dp->name))
		{
			dp = dp->next;
			continue;
		}
		printf("%s\t", dp->name);

		dp = dp->next;
	}
	printf("\n\n");
}

void	swap_dp(t_dp **dp)
{
	char	*t_name;
	int		t_type;

	t_name = (*dp)->next->name;
	t_type = (*dp)->next->type;
	(*dp)->next->name = (*dp)->name;
	(*dp)->next->type = (*dp)->type;
	(*dp)->name = t_name;
	(*dp)->type = t_type;
}
