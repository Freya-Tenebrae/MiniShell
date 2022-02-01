/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 01:20:46 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/01 16:51:50 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Créer un élément */

t_elem	*ft_tools_elem_create(char *str)
{
	t_elem	*list_new;
	int		type;

	type = ft_get_operator_type(str);
	if (type == -1)
		return (NULL);
	if (!str)
	{
		str = ft_strdup("");
		if (!str)
			return (NULL);
	}
	list_new = malloc(sizeof(t_elem));
	if (!list_new)
		return (NULL);
	list_new->next = NULL;
	list_new->str = str;
	list_new->type = type;
	return (list_new);
}

/* Renvoie le dernier élément de la liste */

t_elem	*ft_tools_elem_last(t_elem *list)
{
	t_elem		*list_ptr;

	if (!list)
		return (NULL);
	list_ptr = list;
	while (list_ptr->next != NULL)
		list_ptr = list_ptr->next;
	return (list_ptr);
}

/* Ajoute un élément à la liste, prends un double pointeur */
/* pour créer la liste si elle n'éxiste pas */

int	ft_tools_elem_add(t_elem **list, char *str)
{
	t_elem	*list_new;
	t_elem	*list_ptr;

	if (!list)
		return (-1);
	list_new = ft_tools_elem_create(str);
	if (list_new == NULL)
		return (-1);
	if (!(*list) || *list == NULL)
		*list = list_new;
	else
	{
		list_ptr = ft_tools_elem_last(*list);
		list_ptr->next = list_new;
	}
	return (1);
}
