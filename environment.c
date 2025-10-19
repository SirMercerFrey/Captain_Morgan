#include "minishell.h"

char	*ft_strdup(const char *s)
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


int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

size_t	ft_strlen(char *str)
{
	char	*end;

	if (!str)
		return (0);
	end = str;
	while (*end)
		++end;
	return (end - str);
}

char	*extract_var(char *str)
{
	size_t	len;
	size_t	i;
	char	*var;

	len = 1;
	while (str[len] && ft_isalnum(str[len]))
		++len;
	--len;
	var = (char *)(malloc(sizeof(char) * len + 1));
	if (!var)
		return (NULL);
	++str;
	i = 0;
	while (i < len)
		var[i++] = *str++;
	var[i] = '\0';
	return (var);
}

char	*write_var(char *str, char *env, size_t i, size_t var_len)
{
	char	*new_str;
	size_t	str_len;
	size_t	env_len;
	size_t	j;

	str_len = ft_strlen(str);
	env_len = ft_strlen(env);
	new_str = (char *)malloc(sizeof(char) * (str_len - var_len + env_len + 1));
	j = 0;
	while (j < i)
	{
		new_str[j] = str[j];
		++j;
	}
	while (*env)
		new_str[j++] = *env++;
	i = i + var_len + 1;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	return (new_str);
}

char	*get_var(char *str, size_t i)
{
	char	*new_str;
	char	*var;
	char	*env;
	size_t	var_len;

	var = extract_var(str + i);
	var_len = ft_strlen(var);
	env = getenv(var);
	free(var);
	if (!env)
		env = "";
	new_str = write_var(str, env, i, var_len);
	return (new_str);
}

void	check_var_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !*in_double_quote)
		*in_single_quote = !*in_single_quote;
	else if (c == '"' && !*in_single_quote)
		*in_double_quote = !*in_double_quote;
}

void	put_env_str(char **str)
{
	char	*new_str;
	int		in_single_quote;
	int		in_double_quote;
	size_t	i;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	while ((*str)[i])
	{
		check_var_quotes((*str)[i], &in_single_quote, &in_double_quote);
		if (!in_single_quote && (*str)[i] == '$')
		{
			new_str = get_var(*str, i);
			free(*str);
			*str = new_str;
			i = 0;
			in_single_quote = 0;
			in_double_quote = 0;
			continue ;
		}
		++i;
	}
}

int		main(void)
{
	char	str[] = "\"Hello $USER, you 're now at $PWD on the $HOSTNAME machine.\"";
	char	*s;

	s = ft_strdup(str);
	printf("Original: %s\n", s);	
	put_env_str(&s);
	printf("Final: %s\n", s);
	free(s);
	return (0);
}
