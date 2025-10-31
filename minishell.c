#include "minishell.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

/*void	write_prompt(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(1, cwd, strlen(cwd));
		write(1, " > ", 3);
	}
	else
		write(1, "unknown > ", 10);
}*/

size_t	ft_strlen(const char *str)
{
	const char	*end;

	if (!str)
		return (0);
	end = str;
	while (*end)
		++end;
	return (end - str);
}

static size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	dlen = 0;
	while (dest[dlen] && dlen < size)
		++dlen;
	slen = 0;
	while (src[slen])
		++slen;
	if (dlen >= size)
		return (size + slen);
	i = 0;
	while (src[i] && dlen + i < size -1)
	{
		dest[dlen + i] = src[i];
		++i;
	}
	dest[dlen + i] = '\0';
	return (dlen + slen);
}

static size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = 0;
	while (src[len])
		++len;
	i = 0;
	if (size)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			++i;
		}
		dest[i] = '\0';
	}
	return (len);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	strjoin = (char *)(malloc(sizeof(char) * (len + 1)));
	if (!strjoin)
		return (NULL);
	ft_strlcpy(strjoin, s1, len + 1);
	ft_strlcat(strjoin, s2, len + 1);
	return (strjoin);
}

char	*get_prompt(void)
{
    char 	*cwd;
	char	*prompt;

	cwd = NULL;
    cwd = getcwd(NULL, 0); 
	if (cwd != NULL)
    {
		prompt = ft_strjoin(cwd, " > ");
		free(cwd);
		return (prompt);
    }
    else
    {
        printf("unknown > ");
		return (NULL);
    }
}

void	prompt_loop_sub(char *line, t_shell *minishell)
{
	t_cap	*head;
	t_cmd	*current;
	t_rdr	*tmp;
	char	**token;
	size_t	i;

	token = split_tokens(line);
	if (!all_checks(token))
		return (exit_syntax(token), (void)0);
	put_env_arg(token, minishell->envp);
	remove_quotes(token);
	head = parsing(token);
	printf("There are %d tok in the following command\n", head->tok);
	minishell->cap = head;
	current = head->next;
	while (current)
	{
		i = 0;
		while (current->argv[i])
			printf("argv = %s\n", current->argv[i++]);
		printf("path = %s\n", current->cmd_path);
		tmp = current->redirs;
		while (tmp)
		{
			printf("\tfilename = %s\n", tmp->filename);
			printf("\ttype = %d\n", tmp->type);
			tmp = tmp->next;
		}
		current = current->next;
	}
	free_head_nodes(head);
	i = 0;
	while (token[++i]);
	free_tokens(token, i - 1);
}

void	prompt_loop(t_shell *minishell)
{
	char	*line;
	char	*origin;
	char	*prompt;

	prompt = get_prompt();
	line = readline(prompt);
	while (line != NULL)
	{
		if (*line)
		{
			origin = line;
			prompt_loop_sub(line, minishell);
		}
		free(origin);
		origin = NULL;
		free(prompt);
		prompt = get_prompt();
		line = readline(prompt);
	}
}

/*int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	prompt_loop(envp);
	return (0);
}*/	
