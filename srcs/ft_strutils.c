/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:28:11 by gadeneux          #+#    #+#             */
/*   Updated: 2022/01/20 18:06:22 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Récupère tout ce qui se trouve avant le premier caractère c dans */
/* la chaine str. */

char	*ft_str_before(char *str, char c)
{
	char	*dst;
	int		l;
	int		i;

	if (!str)
		return (0);
	l = 0;
	while (str[l] && str[l] != c)
		++l;
	dst = malloc(l + 1);
	if (!dst)
		return (0);
	i = 0;
	while (str[i] && i < l)
	{
		dst[i] = str[i];
		++i;
	}
	dst[i] = 0;
	return (dst);
}

/* Récupère tout ce qui se trouve après le premier caractère c dans */
/* la chaine str. */

char	*ft_str_after(char *str, char c)
{
	int i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != c)
		i++;
	if (!str[i])
		return (ft_strdup(str));
	if (str[i] == c)
		i++;
	int len = ft_strlen(str) - i;
	char *res = malloc(len + 1);
	if (!res)
		return (0);
	int j = 0;
	while (str[i])
	{
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = 0;
	return (res);
}

/* Concerti un caractère en chaine de caractère */

char		*ft_char_tostring(char c)
{
	char *str = malloc(sizeof(char) * 2);
	if (!str)
		return (0);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

/* Écris un caractère sur la chaine str (Free l'ancien str et remplace). */
/* Si la chaine str n'existe pas elle sera allouée. */

char		*ft_char_writeon(char **str, char c)
{
	if (!str)
		return (0);
	if (!(*str))
	{
		*str = ft_char_tostring(c);
		return (*str);
	}
	char *res = malloc((sizeof(char) * ft_strlen(*str)) + 2);
	if (!res)
		return (0);
	int i = 0;
	while ((*str)[i] != '\0')
	{
		res[i] = (*str)[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = '\0';
	free(*str);
	*str = res;
	res = NULL;
	return (*str);
}

/* Écris une string sur la chaine str (Free l'ancien str et remplace). */
/* Si la chaine str n'existe pas elle sera allouée. */

char		*ft_str_writeon(char **str, char *to_add)
{
	if (!str)
		return (0);
	if (!(*str))
	{
		*str = ft_strdup(to_add);
		return (*str);
	}
	char *res = ft_strjoin(*str, to_add);
	if (!res)
		return (0);
	free(*str);
	*str = res;
	return (res);
}

/* Renvoie true si le caractère c est un whitespace. */

int		ft_str_iswhitespace(char c)
{
	return (c == (char) 32 || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r');
}

/* Alloue une chaine de caractère qui se trouve entre begin et end, dans la chaine str. */

char	*ft_str_substring(char *str, int begin, int end)
{
	char	*res;
	int		i;

	res = 0;
	i = begin;
	if (!str)
		return (0);
	if (begin >= (int) ft_strlen(str) || end >= (int) ft_strlen(str)
			|| begin < 0 || end < 0)
		return (0);
	if (begin > end)
		return (0);
	while (str[i] && i < end)
	{
		ft_char_writeon( & res, str[i]);
		i++;
	}
	return (res);
}

/* Renvoie l'index de la première occurence du caractère c */
/* dans la chaine str, ou -1 si aucun résultat. */

int	ft_str_indexof(char *str, char c)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/* Renvoie l'index de la dernière occurence du caractère c */
/* dans la chaine str, ou -1 si aucun résultat. */

int	ft_str_lastindexof(char *str, int from, char c)
{
	int i = from;
	int res = -1;
	if (from < 0 || from > (int) ft_strlen(str))
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			res = i;
		i++;
	}
	return (res);
}

/* Clone le tableau spécifié. */

char	**ft_str_clonetab(char **strs)
{
	int len = 0;
	while (strs[len])
		len++;
	char **res = malloc(sizeof(char*) * (len + 1));
	if (!res)
		return (0);
	int i = 0;
	while (strs[i])
	{
		res[i] = ft_strdup(strs[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

/* Renvoie true si str1 est égal à str2. */
// equivalent a strcmp ?

int		ft_str_is(char *str1, char *str2)
{
	if (!str1 && !str2)
		return (1);
	if (!str1 || !str2)
		return (0);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	int i = 0;
	int len = ft_strlen(str1);
	while (i < len && str1[i] == str2[i])
		i++;
	return (i == len);
}

/* Free le tableau spécifié */

void	ft_freestrs(char ***strs)
{
	char	**strs_ptr;

	strs_ptr = *strs;
	while (*strs_ptr != NULL)
	{
		free(*strs_ptr);
		*strs_ptr = NULL;
		strs_ptr++;
	}
	free(*strs);
	*strs = NULL;
}


// free lists

void	ft_tools_free_elem(t_elem **elem)
{
	t_elem *elem_ptr;

	elem_ptr = *elem;
	while (elem_ptr != NULL)
	{
		elem_ptr = elem_ptr->next;
		if ((*elem)->str != NULL)
			free((*elem)->str);
		free(*elem);
		*elem = elem_ptr;
	}	
}

void	ft_tools_free_output(t_output **output)
{
	if (output != NULL && *output != NULL)
	{
		if ((*output)->output != NULL)
			free((*output)->output);
		if ((*output)->error != NULL)
			free((*output)->error);	
		free(*output);
	}
}

void	ft_tools_free_env(t_env **env)
{
	if (env != NULL && *env != NULL)
	{
		if ((*env)->value != NULL)
			free((*env)->value);
		if ((*env)->name != NULL)
			free((*env)->name);	
		free(*env);
	}
}

void	ft_tools_free_data(t_data **data)
{
	if (data != NULL && *data != NULL)
	{
		ft_tools_free_env((*data)->env);
		if ((*data)->path != NULL)
			free((*data)->path);	
	}
}
