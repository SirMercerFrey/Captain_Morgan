#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void	write_prompt(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(1, cwd, strlen(cwd));
		write(1, " > ", 3);
	}
	else
		write(1, "unknown > ", 10);
}

void	prompt_loop(char **envp)
{
	char	*line;
	(void)envp;

	write_prompt();
	line = readline("");
	while (line != NULL)
	{
		if (*line)
		{
			printf("%s\n", line);
		}
		free(line);
		write_prompt();
		line = readline("");
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	prompt_loop(envp);
	return (0);
}	
