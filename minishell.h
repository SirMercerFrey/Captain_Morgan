#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h> 

typedef struct	s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	int				append;
	int				heredoc;
	struct s_cmd	*next;
} t_cmd;

typedef struct	s_cap
{
	int				tok;
	struct s_cmd	*next;
} t_cap;

int		check_pipes(char **token);
int		check_redirections(char **token);
int		check_quotes(char **token);
int		all_checks(char **token);
void	remove_outer_quotes_inplace(char *str);
void	remove_quotes(char **argv);

size_t	get_len(char *line);
char	*extract_token(char **line);
void	free_tokens(char **token, int i);
char	**split_tokens(char *line);

void	write_prompt(void);
void	prompt_loop_sub(char *line, char **token);
void	prompt_loop(char **envp);

t_cmd	*create_node(void);
t_cap	*create_head(void);
void	add_arg(char ***argv, char *word);
void	parsing_loop(char **token, t_cmd *node, int *n);
t_cap	*parsing(char **token);
void	free_head_nodes(t_cap *head);

void	print_banner_start(void);
void	print_banner_end(void);



#endif
