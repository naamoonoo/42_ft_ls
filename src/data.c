#include "ft_ls.h"

void		make_linked_fi(char *name, t_ls *ls, int *f_count)
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

void		make_linked_data(struct dirent *p, t_dp **dp,
	int dp_exist, char *name, t_ls ls)
{
	t_dp		*temp;
	struct stat	info;

	temp = malloc(sizeof(t_dp));
	temp->name = p->d_name;
	temp->type = p->d_type;
	temp->curr = ft_strjoin_by(name, p->d_name, "/");
	lstat(temp->curr, &info);
	temp->info = info;
	temp->time_ = get_time(info, ls);
	temp->next = NULL;
	temp->prev = NULL;
	if (dp_exist != 0)
	{
		temp->prev = (*dp);
		(*dp)->next = temp;
	}
	if (is_hidden(temp->name))
		ft_strdel(&temp->curr);
	(*dp) = temp;
}

long int	get_time(struct stat info, t_ls ls)
{
	if (IS_SAME(ls.flag, U_FLAG))
		return (info.st_birthtime);
	else if (IS_SAME(ls.flag, u_FLAG))
		return (info.st_atime);
	return (info.st_mtime);
}
