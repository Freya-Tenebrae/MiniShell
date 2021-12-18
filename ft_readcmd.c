#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_elem {
	struct s_elem	*next;
	int				type;
	char			*str;
}				t_elem;

# define ARGUMENT 0
# define IN 1
# define DOUBLE_IN 2
# define OUT 3
# define DOUBLE_OUT 4
# define PIPE 5

static int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*ft_chartostring(char c)
{
	char *str = malloc(sizeof(char) * 2);
	if (!str)
		return (0);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

static char	*ft_writeon(char **str, char c)
{
	if (!str)
		return (0);
	if (!(*str))
	{
		*str = ft_chartostring(c);
		return (*str);
	}
	int len = ft_strlen(*str);
	char *res = malloc((sizeof(char) * len) + 2);
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
	return (res);
}

static int		ft_iswhitespace(char c)
{
	return (c == (char) 32 || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r');
}

static int		ft_readnext(char *str, int i, char **buffer)
{
	if (!str)
		return (-1);
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	while (str[i] && !ft_iswhitespace(str[i]))
	{
		if (!ft_writeon(buffer, str[i]))
			return (-1);
		i++;
	}
	return (i);
}

static int		ft_stris(char *str1, char *str2)
{
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	int i = 0;
	int len = ft_strlen(str1);
	while (i < len && str1[i] == str2[i])
		i++;
	return (i == len);
}

static int		ft_gettype(char *str)
{
	if (ft_stris(str, "<"))
		return (IN);
	if (ft_stris(str, "<<"))
		return (DOUBLE_IN);
	if (ft_stris(str, ">"))
		return (OUT);	
	if (ft_stris(str, ">>"))
		return (DOUBLE_OUT);
	if (ft_stris(str, "|"))
		return (PIPE);
	return (-1);
}

static int		ft_isoperator(char *str)
{
	return (ft_gettype(str) != -1);
}

static t_elem	*ft_createelem(char *str)
{
	t_elem *res = malloc(sizeof(t_elem));
	if (!res)
		return (0);
	res->next = 0;
	res->str = str;
	res->type = ft_gettype(str);
	return (res);
}

static t_elem	*ft_lastelem(t_elem *list)
{
	if (!list)
		return (0);
	t_elem *cursor = list;
	while (cursor->next != 0)
		cursor = cursor->next;
	return (cursor);
}

static int		ft_addon(t_elem **list, char *str)
{
	int label = !(*list);
	if (!list)
		return (-1);
	if (!(*list))
	{
		*list = ft_createelem(str);
		(*list)->type = ARGUMENT;
		if (!*list)
			return (-1);
		return (1);
	}
	t_elem *last = ft_lastelem(*list);
	if (!last)
		return (-1);
	last->next = ft_createelem(str);
	if (last->next->type == -1)
		last->next->type = ARGUMENT;
	return (1);
}

t_elem	*ft_readcmd(char *str)
{
	int	i = 0;
	char *buffer = 0;
	t_elem *list = 0;
	if (!str)
		return (0);
	while ((i = ft_readnext(str, i, &buffer)) < ft_strlen(str) && i != -1)
	{
		if (!ft_addon(&list, buffer))
			return (0);
		buffer = 0;
	}
	if (i == -1)
		return (0);
	if (buffer)
		free(buffer);
	return (list);
}

int		main(int ac, char **av)
{
	t_elem *list = ft_readcmd("   input < cat -e test.sh | | grep script.sh > output");
	if (!list)
	{
		printf("Error\n");
		return (0);
	}
	while (list)
	{
		printf("%-10s [%d]\n", list->str, list->type);
		list = list->next;
	}
	return (0);
}