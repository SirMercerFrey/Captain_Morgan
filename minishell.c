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

void write_prompt(void)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s > ", cwd);
    }
    else
    {
        printf("unknown > ");
    }
}

void	prompt_loop_sub(char *line, char **token)
{
	t_cap	*head;
	t_cmd	*current;
	t_rdr	*tmp;
	size_t	i;

	token = split_tokens(line);
	if (!all_checks(token))
		return (exit_syntax(token), (void)0);
	put_env_arg(token);
	remove_quotes(token);
	head = parsing(token);
	printf("There are %d tok in the following command\n", head->tok);
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

void	prompt_loop(char **envp)
{
	char	*line;
	char	*origin;
	char	**token;
	(void)envp;

	write_prompt();
	line = readline("");
	while (line != NULL)
	{
		if (*line)
		{
			token = NULL;
			origin = line;
			prompt_loop_sub(line, token);
		}
		free(origin);
		origin = NULL;
		write_prompt();
		line = readline("");
	}
}

/*int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	prompt_loop(envp);
	return (0);
}*/	
