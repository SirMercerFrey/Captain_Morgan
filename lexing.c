#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#define TOK_MAX 128

static int		metachars(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int		quotes(char c)
{
	return (c == '\'' || c == '"');
}


static int		spaces(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

size_t	get_len(char *line)
{
	size_t	i;
	char	c;

	if (metachars(line[0]))
	{
		if (line[1] && line[1] == line[0])
			return (2);
		return (1);
	}
	i = 0;
	while (line[i] && !metachars(line[i]) && !spaces(line[i]))
	{
		if (quotes(line[i]))
		{
			c = line[i++];
			while (line[i] && line[i] != c)
				++i;
			if (!line[i])
				break;
		}
		++i;
	}
	return (i);
}
			
char	*extract_token(char **line)
{
	size_t	len;
	size_t	i;
	char	*token;

	len = get_len(*line);
	token = malloc(sizeof(char) * (len + 1));
	if (!token)
		return (NULL);
	i = 0;
	while (i < len)
	{
		token[i] = (*line)[i];
		++i;
	}
	token[len] = '\0';
	*line += len;
	return (token);
}	

void	free_tokens(char **token, int i)
{
	while (i >= 0)
	{
		free(token[i]);
		--i;
	}
	free(token);
} 
	
char	**split_tokens(char *line)
{
	int		i;
	char	**token;

	token = malloc(sizeof(char *) * TOK_MAX);
	if (!token)
		return (NULL);
	i = 0;
	while (*line && i < TOK_MAX)
	{
		while (*line && spaces(*line))
			++line;
		token[i] = extract_token(&line);
		if (!token[i])
		{
			free_tokens(token, i - 1);
			return (NULL);
		}
		++i;
	}
	token[i] = NULL;
	return (token);
}

/*int		main(void)
{
	char	*line;
	line = readline("Prompt >");
	char **token;
	char *origin = line;
	token = split_tokens(line);
	size_t i = 0;
	while (token[i])
		printf("%s\n", token[i++]);
	free_tokens(token, i - 1);
	free(origin);
	return (0);
}*/	
