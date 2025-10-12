#include "minishell.h"


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	print_banner_start();
	prompt_loop(envp);
	print_banner_end();
	return (0);
}
