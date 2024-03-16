/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:07:02 by ychng             #+#    #+#             */
/*   Updated: 2024/03/16 19:05:35 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "sys_headers.h"
# include "libft.h"

typedef struct s_subtoken_node
{
	char					*subtoken;
	struct s_subtoken_node	*next;
	struct s_subtoken_node	*prev;
}	t_subtoken_node;

typedef struct s_subtoken_list
{
	t_subtoken_node	*head;
	t_subtoken_node	*tail;
}	t_subtoken_list;

typedef struct s_token_node
{
	t_subtoken_list		*subtoken_list;
	struct s_token_node	*next;
	struct s_token_node	*prev;
}	t_token_node;

typedef struct s_token_list
{
	t_token_node	*head;
	t_token_node	*tail;
}	t_token_list;

// character_check_1.c
bool			is_backslash(char c);
bool			is_single_quote(char c);
bool			is_double_quote(char c);
bool			is_quote(char c);
bool			is_delim(char c, char *delim);

// character_check_2.c
bool			is_underscore(char c);
bool			is_hash(char c);
bool			is_dollar_sign(char c);
bool			is_asterisk(char c);
bool			is_ampersand(char c);

// character_check_3.c
bool			is_question_mark(char c);
bool			is_exclamation(char c);
bool			is_number(char c);
bool			is_uppercase(char c);
bool			is_lowercase(char c);

// character_check_4.c
bool			is_tilde(char c);
bool			is_newline(char c);
bool			is_escapable(char c);
bool			is_space(char c);
bool			is_sign(char c);

// character_check_5.c
bool			is_equal(char c);
bool			is_left_bracket(char c);
bool			is_right_bracket(char c);
bool			is_bracket(char c);
bool			is_pipe(char c);

// operator_check.c
bool			is_logical_operator(char *str);
bool			is_logical_operator_n(char *str);
bool			is_redirection_n(char *str);
bool			is_heredoc(char *str);

// builtins/blt_echo_utils.c
bool			is_n_options(char *subtoken);
t_subtoken_node	*find_first_non_option(t_subtoken_node *params);

// builtins/blt_echo.c
void			blt_echo(t_subtoken_node *params);

// builtins/blt_pwd.c
void			blt_pwd(void);

// builtins/blt_export_utils_1.c
t_subtoken_list	*create_params_list(void);
char			**alloc_export_envp(char **envp, t_subtoken_node *params);
void			copy_to_dest(char **dest, char **envp, t_subtoken_node *params);
void			pad_export_envp(char **export_envp);
void			radix_sort(char **export_envp);

// builtins/blt_export_utils_2.c
t_subtoken_node	*filter_params(t_subtoken_node *params);
char			**create_valid_envp(char **envp, t_subtoken_node *valid_params);
void			print_export_envp(char **export_envp);
void			free_envp(char **envp);

// builtins/blt_export_utils_3.c
int				count_envp_size(char **envp);
int				count_params_size(t_subtoken_node *params);
void			from_envp(char **export_envp, char **envp);
void			from_params(char **export_envp, t_subtoken_node *params);
int				get_max_name_len(char **export_envp);

// builtins/blt_export_utils_4.c
char			*pad_name(char *entry, int max_name_len);
void			count_sort(char **export_envp, int export_envp_size, int pos);

// builtins/blt_export_utils_5.c
bool			validate_entry_name(char *subtoken);
char			**create_output(int export_envp_size);

// builtins/blt_export.c
void			blt_export(char ***envp, t_subtoken_node *params, \
					t_subtoken_list *params_list);

// builtins/blt_unset.c
void			blt_unset(char **envp, t_subtoken_node *params, \
					t_subtoken_list *params_list);

// builtins/blt_env.c
void			blt_env(char **envp);

// builtins/blt_exit_utils.c
bool			contain_only_digits(char *first_arg);
int				normalize_exit_code(char *first_arg);
void			handle_numeric_exit(char *first_arg, char *dup_subtoken);
void			handle_non_numeric_exit(char *dup_subtoken);

// builtins/blt_exit.c
void			blt_exit(t_subtoken_node *params);

// clone_double_array.c
char			**clone_double_array(char **double_array);

// quote_handling.c
void			toggle_in_quote(char c, bool *in_quote, char *quote_type);

// get_next_token_utils.c
int				len_of_operator(char *remaining_input);
bool			is_bracket_or_logical_operator(char *remaining_input);

// get_next_token.c
char			*get_next_token(char *input);

// get_next_subtoken_utils.c
int				len_of_redirection(char *subtoken);
bool			is_space_or_redirection(char *subtoken);

// get_next_subtoken.c
char			*get_next_subtoken(char *token);

// custom_strtok.c
char			*custom_strtok(char *input, char *delim);

// env_check.c
bool			is_special_env_name(char c);
bool			is_valid_env_name(char c);
bool			is_env_var(char *remaining_input);

// get_next_env.c
char			*get_next_env(char *subtoken);

// string_utils.c
char			*custom_strjoin(char *s1, char *s2);

// get_input_line_utils.c
bool			has_open_quote(char *final_input);
char			*normalize_input(char *temp_input);

// get_input_line.c
char			*get_input_line(void);

// expand_env_utils.c
int				count_len_until_env(char *subtoken, char *env);
char			*get_env_value(char *env);
int				count_env_value_len(char *env);
int				skip_env(char *env);
char			*append_env_value(char *result, char *env);

// expand_env.c
char			*expand_env(char *subtoken);

// expand_tilde_utils_1.c
int				count_valid_key_name(char *subtoken);
char			*extract_until_delim(char *user, char *delim);
char			*find_user_directory(char *user);

// expand_tilde_utils_2.c
DIR				*open_users_directory(void);
char			*find_home_directory(char *entry_name, char *user);
char			*extract_key(char *subtoken);

// expand_tilde_helper.c
char			*join_expanded_tilde_with_remains(char *directory, \
					char *remains);
char			*join_key_with_value(char *value, char *subtoken);

// expand_tilde.c
char			*expand_tilde(char *subtoken);

// get_next_line_utils.c
bool			contains_newline(char *remaining_line);
int				read_and_check(int fd, char *buffer, int buffer_size);

// get_next_line.c
char			*get_next_line(int fd);

// expand_escaped_utils.c
bool			should_escape(char quote_type, char *subtoken);

// expand_escaped.c
char			*expand_escaped(char *subtoken);

// subtoken_list_utils_1.c
t_subtoken_node	*create_subtoken_node(char *subtoken);
t_subtoken_list	*create_subtoken_list(void);
t_subtoken_node	*pop_subtoken_list_head(t_subtoken_list *subtoken_list);
t_subtoken_node	*pop_subtoken_list_tail(t_subtoken_list *subtoken_list);
void			link_subtoken_list(t_subtoken_node *subtoken_node, \
					t_subtoken_list *subtoken_list);

// subtoken_list_utils_2.c
int				count_subtoken_list(t_subtoken_list *subtoken_list);

// token_list_utils.c
t_token_node	*create_token_node(t_subtoken_list *subtoken_list);
t_token_list	*create_token_list(void);
t_token_node	*pop_token_list_head(t_token_list *token_list);
t_token_node	*pop_token_list_tail(t_token_list *token_list);
void			link_token_list(t_token_node *token_node, \
					t_token_list *token_list);

// get_token_list_utils.c
char			*expand_subtoken(char *subtoken, bool expand_heredoc);

// get_token_list.c
t_token_list	*get_token_list(char *input);

// infix_to_postfix_utils.c
char			*first_subtoken(t_token_node *current_tok);
int				priority(t_token_node *current_tok);

// infix_to_postfix.c
t_token_list	*infix_to_postfix(t_token_list *infix);

// evaluate_postfix.c
void			evaluate_postfix(char ***envp, t_token_list *postfix);

// free_list.c
void			free_subtoken_node(t_subtoken_node *subtoken_node);
void			free_subtoken_list(t_subtoken_list *subtoken_list);
void			free_token_node(t_token_node *token_node);
void			free_token_list(t_token_list *token_list);

#endif
