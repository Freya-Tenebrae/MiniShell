/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 00:54:38 by gadeneux          #+#    #+#             */
/*   Updated: 2022/01/25 03:13:55 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_lenght_args(t_elem *list)
{
	int		i;
	t_elem	*pos_list;

	i = 0;
	pos_list = list;
	while (pos_list != NULL && pos_list->type != PIPE)
	{
		if (pos_list->type == IN || pos_list->type == DOUBLE_IN || \
			pos_list->type == OUT || pos_list->type == DOUBLE_OUT)
			pos_list = pos_list->next->next;
		else
		{
			i++;
			pos_list = pos_list->next;
		}
	}
	return (i);
}

static t_elem	*ft_put_args_in_cmd_args(t_elem *list, char ***cmd_args)
{
	int		i;

	i = ft_lenght_args(list);
	*cmd_args = malloc(sizeof(char *) * (i + 1));
	if (!*cmd_args)
		return (NULL);
	i = 0;
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == IN || list->type == DOUBLE_IN || \
			list->type == OUT || list->type == DOUBLE_OUT)
			list = list->next->next;
		else
		{
			(*cmd_args)[i] = ft_strdup(list->str);
			list = list->next;
			i++;
		}
	}
	(*cmd_args)[i] = NULL;
	return (list);
}

// ft_put_out va creer les fichier si ils n'existent pas, et supprimer le 
//		contenus du fichier si celui-ci est preceder de >

// run cmd dois :
//	- recuperer tous les ARGUMENTS sauf si il sont preceder de < << > ou de >>
//		et les mettres dans cmd_args
//	- si > et/ou >> present, apeller la fonction ft_put_out a chacune des 
//		occurence , puis recuperer la deriere occurence et la stocker dans 
//		une variable "char *file_out"
//	- si < et/ou << recuperer la deriere occurence et la stocker dans une 
//		structure "t_rdirection_in" contenant "char *file_in" et 
//		"int is_double_in"
//	- regarder si il s'agit d'un build-in ou non et apeller la fonction 
//		correspondante
// 			//supprimer path et apeller getenv directement depuis execve ?
//		(*out = ft_run_bi(cmd_args, *infile, file_out, t_rdirection_in))
//		(*out = ft_exec_cmd(cmd_args, *infile, file_out, t_rdirection_in))
//		{
//				dans ses 2 commande si t_redirection_in != NULL il faudra 
//					ignorer infile et utiliser la bonne redirection de fd sur
//					stdin vers le fork
//				si file_out != NULL il faudra rediriger out->output vers
//					file_out uniquement, set infile a NULL et out->output = ""
//				pour les output si il n'y a pas d'erreur d'execve, out->output 
//					ne devra ni etre non attribuer ni nul et out->error devra 
//					etre NULL
//				dans le cas ou il y aurais une erreur elle devra etre mise dans
//					out->error (argument, fonction didn't exist, ...) et 
//					out->output devra etre set a NULL;
//		}
//	- dans le cas out->output n'est pas null et ou 
//	- dans le cas out->output n'est pas null et ou la position de list pointe
//		sur NULL il faudra afficher le resultat sur l'entree standard
//	- dans le cas out->output == NULL il faudra afficher l'erreur out->error
//	- dans le cas ou la position de list pointe sur un PIPE il faudra juste 
//		passer a list = list->next;

static void	ft_redirection_cmd(t_output	**out, t_elem **list, char **infile)
{
	char		**cmd_args;

	*list = ft_put_args_in_cmd_args(*list, &cmd_args);
	if (ft_tools_is_build_in(cmd_args[0]) == 0)
		*out = ft_run_bi(g_minishell->path, cmd_args, *infile);
	else
		*out = ft_exec_cmd(g_minishell->path, cmd_args, *infile);
	ft_freestrs(&cmd_args);
}

t_elem	*ft_run_cmd(t_elem *list, char **infile)
{
	t_output	*out;

	ft_redirection_cmd(&out, &list, infile);
	free(*infile);
	if (out->output)
	{
		ft_putstr_fd(out->output, STDOUT_FILENO);
		*infile = ft_strdup(out->output);
		if (!infile)
		{
			infile = NULL;
			return (NULL);
		}
	}
	else
	{
		ft_putstr_fd(out->error, STDOUT_FILENO);
		infile = NULL;
	}
	ft_tools_free_output(&out);
	return (list);
}
