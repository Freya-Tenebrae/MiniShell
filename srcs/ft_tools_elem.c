/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 01:20:46 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/06 15:48:38 by cmaginot         ###   ########.fr       */
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
			return (ft_put_error_null(GENERIC_ERROR, "malloc error"));
	}
	type = ft_get_operator_type(str);
	list_new = malloc(sizeof(t_elem));
	if (!list_new)
		return (ft_put_error_null(GENERIC_ERROR, "malloc error"));
	list_new->next = NULL;
	list_new->str = str;
	list_new->in_content = NULL;
	list_new->out_fd = -1;
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
