/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 01:20:46 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/27 15:42:28 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Créer un élément */

t_elem	*ft_elem_create(char *str, int is_operator)
{
	t_elem	*list_new;
	int		type;

	if (!str)
	{
		str = ft_strdup("");
		if (!str || str == NULL)
		{
			ft_put_error(GENERIC_ERROR, "malloc error");
			return (NULL);
		}
	}
	type = ft_get_operator_type(str);
	list_new = malloc(sizeof(t_elem));
	if (!list_new)
	{
		ft_put_error(GENERIC_ERROR, "malloc error");
		return (NULL);
	}
	list_new->next = NULL;
	list_new->str = str;
	list_new->in_content = NULL;
	if (is_operator == 1)
		list_new->type = ARGUMENT;
	else
		list_new->type = type;
	return (list_new);
}

/* Renvoie le dernier élément de la liste */

t_elem	*ft_elem_last(t_elem *list)
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

int	ft_elem_add(t_elem **list, char *str, int is_operator)
{
	t_elem	*list_new;
	t_elem	*list_ptr;

	if (!list)
		return (-1);
	list_new = ft_elem_create(str, is_operator);
	if (list_new == NULL)
		return (-1);
	if (!(*list) || *list == NULL)
		*list = list_new;
	else
	{
		list_ptr = ft_elem_last(*list);
		list_ptr->next = list_new;
	}
	return (0);
}
