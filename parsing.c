#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

t_rdr	*create_redir(void)
{
	t_rdr	*new_redir;

	new_redir = (t_rdr *)(malloc(sizeof(t_rdr)));
	if (!new_redir)
		return (NULL);
	new_redir->type = 42;
	new_redir->filename = NULL;
	new_redir->next = NULL;
	return (new_redir);
}
	
t_cmd	*create_node(void)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)(malloc(sizeof(t_cmd)));
	if (!new_node)
		return (NULL);
	new_node->argv = NULL;
	new_node->cmd_path = NULL;
	new_node->redirs = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_cap	*create_head(void)
{
	t_cap	*new_head;

	new_head = (t_cap *)(malloc(sizeof(t_cap)));
	if (!new_head)
		return (NULL);
	new_head->tok = 0;
	new_head->next = NULL;
	return (new_head);
}

static int		ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		++s1;
		++s2;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

static char	*ft_strdup(const char *s)
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
}

static int	is_redir(char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "<"))
		return (1);
	if (!ft_strcmp(str, ">"))
		return (1);
	if (!ft_strcmp(str, "<<"))
		return (1);
	if (!ft_strcmp(str, ">>"))
		return (1);
	return (0);
}

void	add_arg(char ***argv, char *word)
{
	size_t	count;
	size_t	i;
	char	**new_argv;

	count = 0;
	while (*argv && (*argv)[count])
		++count;
	new_argv = malloc(sizeof(char *) * (count + 2));
	i = 0;
	while (i < count)
	{
		new_argv[i] = (*argv)[i];
		++i;
	}
	new_argv[count] = ft_strdup(word);
	new_argv[count + 1] = NULL;
	free(*argv);
	*argv = new_argv;
}

void	handle_direction(char **token, t_cmd *node, int *n)
{
	t_rdr	*new;
	t_rdr	*tmp;

	new = create_redir();
	tmp = node->redirs;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		node->redirs = new;
	if (!ft_strcmp(token[*n], "<"))
		new->type = 0;
	else if (!ft_strcmp(token[*n], ">"))
		new->type = 1;
	else if (!ft_strcmp(token[*n], "<<"))
		new->type = 2;
	else if (!ft_strcmp(token[*n], ">>"))
		new->type = 3;
	new->filename = ft_strdup(token[++*n]);
}

void	parsing_loop(char **token, t_cmd *node, int *n)
{
	t_cmd	*new;

	while (token[*n])
	{
		if (!ft_strcmp(token[*n], "|"))
		{
			new = create_node();
			node->next = new;
			node = new;
		}
		else if (is_redir(token[*n])) 
			handle_direction(token, node, n);
		else
			add_arg(&node->argv, token[*n]);
		++*n;
	}
}


t_cap *parsing(char **token)
{
	t_cmd	*node;
	t_cap	*head;
	int		nbr_tok;

	head = create_head();
	if (!head)
		return (NULL);
	node = create_node();
	if (!node)
	{
		free(head);
		return (NULL);
	}
	head->next = node;
	nbr_tok = 0;
	parsing_loop(token, node, &nbr_tok);
	head->tok = nbr_tok;
	return (head);
}

void	free_redirs(t_rdr *tmp)
{
	t_rdr	*prev;

	while (tmp)
	{
		free(tmp->filename);
		prev = tmp;
		tmp = tmp->next;
		free(prev);
	}
}

void	free_head_nodes(t_cap *head)
{
	t_cmd	*current;
	t_cmd	*previous;
	t_rdr	*tmp;
	size_t	i;

	current = head->next;
	while (current)
	{
		i = 0;
		while (current->argv[i])
			free(current->argv[i++]);
		free(current->argv);
		free(current->cmd_path);
		tmp = current->redirs;
		free_redirs(tmp);
		previous = current;
		current = current->next;
		free(previous);
	}
	free(head);
}
	
		

/*int		main(void)
{
//	char	*token[] = {"echo", "-n", "\"Je suis\"", "une legende", ">>", "file.txt", NULL};
	char	*token[] = {"ls", "-A", "|", "grep", "'user'", NULL};
	t_cap	*head;
	t_cmd	*current;
	size_t i = 0;
	while (token[i])
	{
		printf("%s\n", token[i]);
		++i;
	}
	head = parsing(token);
	current = head->next;
	printf("Nbre cmd = %d\n\n", head->tok);
	while (current)
	{
		size_t	j = 0;
		while (current->argv[j])
			printf("argv = %s\n", current->argv[j++]);
		printf("infile = %s\n", current->infile);
		printf("outfile = %s\n", current->outfile);
		printf("append = %d and heredoc = %d\n\n", current->append, current->heredoc);
		current = current->next;
	}
	free_head_nodes(head);
	return (0);
}*/
