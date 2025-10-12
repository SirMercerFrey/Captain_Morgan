#include "minishell.h"
#include <stdio.h>

void	print_banner_start(void)
{
	printf("\033[1;32m"); // vert
	printf("\t\t\t╔══════════════════════════╗\t\t\t\n");
	printf("\t\t\t║                          ║\n");
	printf("\t\t\t║      MINISHELLBY 42      ║\t\t\t\n");
	printf("\t\t\t║                          ║\n");	
	printf("\t\t\t╚══════════════════════════╝\t\t\t\n");
	printf("\033[0m");
}

void	print_banner_end(void)
{
	printf("\033[1;37m"); // blanc gras
	printf("\t\t\t\t\t\t╔══════════════════════════════════════════╗\n");
	printf("\t\t\t\t\t\t║    \033[1;31mBy order of the Peaky Blinders.\033[1;37m       ║\n");
	printf("\t\t\t\t\t\t╚══════════════════════════════════════════╝\n");
	printf("\033[0m"); 
}


/*int	main(void)
{
	print_banner_start();
	print_banner_end();
	return (0);
}*/
