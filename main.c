#include "minishell.h"

t_shell	*create_shell(char **envp)
{
	t_shell		*new_shell;

	new_shell = (t_shell *)(malloc(sizeof(t_shell)));
	if (!new_shell)
		return (NULL);
	new_shell->cap = NULL;
	new_shell->envp = envp;
	new_shell->exit_status = 42;
	return (new_shell);
}


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_shell		*minishell;

	minishell = create_shell(envp);	
	if (!minishell)
		return (1);
	print_banner_start();
	prompt_loop(minishell);
	free(minishell); //pas encore cree my_envp
	print_banner_end();
	return (0);
}
