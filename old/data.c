#include "ft_ls.h"

t_fi	*get_fi_data(char *av[], t_ls *ls)
{
	int 		i;
	int			arg_started;
	t_fi		*fi;
	DIR			*dirp;
	struct stat	info;

	i = 0;
	arg_started = 1;
	while (av[++i])
	{
		if (ft_start_with(av[i], '-') && arg_started)
			ls->flag = get_ls_flag(&av[i][1]);
		else if((dirp = opendir(av[i])) != NULL)
			link_fi_data(av[i], dirp, info, &fi, &arg_started);
		else if((lstat(av[i], &info)) == 0)
			link_fi_data(av[i], NULL, info, &fi, &arg_started);
		else
			error_alert(INVALID_INPUT, av[i]);
	}
	arg_started ? 0 : fi_set_to_head(&fi);
	return (fi);
}

void	link_fi_data(char *name, DIR *dirp, struct stat info,
	t_fi **fi, int *arg_started)
{
	static int	counter = 1;
	t_fi		*temp;
	temp = malloc(sizeof(t_fi));
	temp->name = name;
	temp->dirp = dirp;
	temp->info = info;
	temp->next = NULL;
	temp->prev = NULL;
	if (counter != 1)
	{
		temp->prev = (*fi);
		(*fi)->next = temp;
	}
	counter++;
	(*fi) = temp;
	*arg_started = 0;
}


