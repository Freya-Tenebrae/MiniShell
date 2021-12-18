#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_elem {
	struct s_elem	*next;
	int				type;
	char			*str;
}				t_elem;

# define LABEL 0
# define ARGUMENT 1
# define OPERATOR 2

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

int		ft_iswhitespace(char c)
{
	return (c == (char) 32 || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r');
}

static int	ft_readnext(char *str, int i, char **buffer)
{
	if (!str)
		return (0);
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	while (str[i] && !ft_iswhitespace(str[i]))
	{
		ft_writeon(buffer, str[i]);
		i++;
	}
	return (i);
}

int	ft_readcmd(char *str)
{
	int	i = 0;
	char *buffer = 0;
	if (!str)
		return (0);
	while ((i = ft_readnext(str, i, &buffer)) < ft_strlen(str))
	{
		printf("\"%s\"\n", buffer);
		buffer = 0;
	}
	printf("\"%s\"\n", buffer);
	return (1);
}

int		main(int ac, char **av)
{
	ft_readcmd("cat -e            test.sh &&         grep script.sh");
	return (0);
}