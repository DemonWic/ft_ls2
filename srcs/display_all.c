/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 16:11:39 by ahintz            #+#    #+#             */
/*   Updated: 2019/11/16 19:30:16 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file	*read_folder(char path[PATH_MAX], char *name, int flags)
{
	t_file			*begin;
	DIR				*folder;
	struct dirent	*entry;

	begin = NULL;
	if (!(folder = opendir(path)))
		ls_error(name, 0);
	else if (!(flags & LS_D))
	{
		while ((entry = readdir(folder)))
			if (entry->d_name[0] != '.' || (flags & LS_A))
				add_new_file(path, entry->d_name, &begin);
	}
	else
		add_new_file(path, ".", &begin);
	if (folder)
		closedir(folder);
	return (begin);
}

static void		display_full_path(char *full_path, int number, int *first)
{
	if (number != 0 && number != 1)
	{
		if (*first == 2)
		{
			*first = 1;
			ft_printf("%s:\n", full_path);
		}
		else
			ft_printf("\n%s:\n", full_path);
	}
}

int				display_all(t_file *root, int flags, int first, int n)
{
	t_file			*file;

	file = root;
	if (!(flags & LS_RR) && !first)
		return (1);
	while (file)
	{
		if (S_ISDIR(file->mode) && (first || (ft_strcmp(file->name, ".")
			&& ft_strcmp(file->name, ".."))))
		{
			display_full_path(file->full_path, n, &first);
			root = read_folder(file->full_path, file->name, flags);
			if (root)
			{
				display_list(&root, flags);
				display_all(root, flags, 0, -1);
				free_list_content(&root);
			}
		}
		file = file->next;
	}
	return (1);
}
