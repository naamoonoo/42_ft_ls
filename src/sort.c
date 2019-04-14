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
	int			len;

	len = get_fi_len(*fi);
	while (len-- > 0)
	{
		while ((*fi)->next)
		{
			// printf("%s and %s is compared\n",(*fi)->name, (*fi)->next->name);
			if (ft_strcmp((*fi)->name, (*fi)->next->name) > 0)
			{
				// printf("would be swaped\n");
				swap_fi(fi);
				// printf("%s and %s is swaped\n",(*fi)->name, (*fi)->next->name);
			}
			(*fi) = (*fi)->next;
		}
		fi_set_to_head(fi);
	}
}
