#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int     ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		++s1;
		++s2;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int		check_pipes(char **token)
{
	size_t	i;

	if (!ft_strcmp(token[0], "|"))
		return (0);
	i = 0;
	while (token[i] && token[i + 1])
	{
		if (!ft_strcmp(token[i], "|") && !ft_strcmp(token[i], token[i + 1]))
			return (0);
		++i;
	}
	if (!ft_strcmp(token[i], "|"))
		return (0);
	return (1);
}

static int		is_redir(char c)
{
	return (c == '>' || c == '<');
}

int		check_redirections(char **token)
{
	size_t	i;

	i = 0;
	while (token[i] && token[i + 1])
	{
		if (is_redir(token[i][0]) && is_redir(token[i + 1][0]))
			return (0);
		++i;
	}
	if (is_redir(token[i][0]))
		return (0);
	return (1);
}

int		check_quotes(char **token)
{
	int		in_single_quote;
	int		in_double_quote;
	size_t	i;
	size_t	j;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	while (token[i])
	{
		j = 0;
		while (token[i][j])
		{
			if (token[i][j] == '\'' && in_double_quote == 0)
				in_single_quote = !in_single_quote;
			else if (token[i][j] == '"' && in_single_quote == 0)
				in_double_quote = !in_double_quote;
			++j;
		}
		++i;
	}
	return (in_single_quote == 0 && in_double_quote == 0);
}

int		all_checks(char **token)
{
	if (!check_pipes(token))
		return (0);
	if (!check_redirections(token))
		return (0);
	if (!check_quotes(token))
		return (0);
	return (1);
}

static size_t	ft_strlen(char *str)
{
	char	*end;

	if (!str)
		return (0);
	end = str;
	while (*end)
		++end;
	return (end - str);
}

void	exit_syntax(char **token)
{
	int		i;
//	char	*red;

//	red = "\033[0;31m";
//	write(2, red, ft_strlen(red));
	write(2, "Syntax error.\n", ft_strlen("Syntax error.\n"));
//	write(2, red, ft_strlen(red));
	i = 0;
	while (token[++i]);
	free_tokens(token, i - 1);
}

void	remove_outer_quotes_inplace(char *str)
{
	int		in_single_quote;
	int		in_double_quote;
	size_t	read;
	size_t	write;

	in_single_quote = 0;
	in_double_quote = 0;
	read = 0;
	write = 0;
	while (str[read])
	{
		if (str[read] == '\'' && in_double_quote == 0)	
		{
			in_single_quote = !in_single_quote;
			++read;
		}
		else if (str[read] == '"' && in_single_quote == 0)
		{
			in_double_quote = !in_double_quote;
			++read;
		}
		else
			str[write++] = str[read++];
	}
	str[write] = '\0';
}

void	remove_quotes(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
	{
		remove_outer_quotes_inplace(argv[i]);
		++i;
	}
}

/*static char	*ft_strdup(const char *s)
{
	char	*dup;
	int		len;
	int		i;

	len = 0;
	while (s[len])
		++len;
	dup = (char *)(malloc(sizeof(char) * (len + 1)));
	if (!dup)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		dup[i] = s[i];
		++i;
	}
	return (dup);
}*/


/*int		main(void)
{
	const char	*orig[] = {"\"echo\"", "ab\"cd\"'ef'", 'Je suis une ''*'\"", "'>'", "\"outfile.txt\"", NULL};
	char	*token[10];

	size_t	i = 0;
	while (orig[i])
	{
		token[i] = ft_strdup(orig[i]);
		++i;
	}
	token[i] = NULL;
	i = 0;
	while (token[i])
		printf("%s\n", token[i++]);
	if (all_checks(token))
	{
		remove_quotes(token);
		i = 0;
		while (token[i])
			printf("%s ", token[i++]);
		printf("\n");
	}
	i = 0;
	while (token[i])
	    free(token[i++]);	
	return (0);
}*/
