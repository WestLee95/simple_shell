#ifndef MY_SHELL_H_
#define MY_SHELL_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environment */
extern char **my_environment;
/* Global program name */
extern char *shell_name;
/* Global history counter */
extern int history_count;

/**
 * struct directory_list - A linked list to hold directories.
 * @path: A directory path.
 * @next: A pointer to another directory_list node.
 */
typedef struct directory_list
{
	char *path;
	struct directory_list *next;
} dir_list_t;

/**
 * struct builtin_command - A struct to define builtin commands.
 * @name: The name of the builtin command.
 * @function: A function pointer to the command's function.
 */
typedef struct builtin_command
{
	char *name;
	int (*function)(char **args, char **args_start);
} builtin_cmd_t;

/**
 * struct alias_entry - A struct to define aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another alias_entry.
 */
typedef struct alias_entry
{
	char *name;
	char *value;
	struct alias_entry *next;
} alias_entry_t;

/* Global alias linked list */
alias_entry_t *my_aliases;

/* Main Helpers */
ssize_t my_getline(char **line, size_t *size, FILE *stream);
void *my_reallocate(void *ptr, unsigned int old_size, unsigned int new_size);
char **my_strtok(char *str, char *delimiters);
char *get_command_location(char *command);
dir_list_t *get_search_path(char *dir);
int custom_execute(char **args, char **args_start);
int execute_command(char *command, char **args, char **args_start, int execute_flag);
int execute_child_process(char *command, char **args, char **args_start);
int wait_for_child_process(pid_t child_pid);
int handle_non_interactive_mode(char *file_path);
int handle_interactive_mode();
void free_directory_list(dir_list_t *list);
char *int_to_string(int num);

/* Input Helpers */
void handle_line(char **args, ssize_t line_length);
void perform_variable_replacement(char **args, int *arg_count);
char *get_arguments(char *line, int *arg_count);
int call_command(char **args, char **args_start, int *exit_status);
int run_command(char **args, char **args_start, int *exit_status);
int handle_command(int *exit_status);
int check_command(char **args);
void custom_signal_handler(int signum);
void free_arguments(char **args, char **args_start);
char **replace_aliases(char **args);

/* String functions */
int my_strlen(const char *str);
char *my_strcat(char *dest, const char *src);
char *my_strncat(char *dest, const char *src, size_t n);
char *my_strcpy(char *dest, const char *src);
char *my_strchr(char *str, char c);
int my_strspn(char *str, char *accept);
int my_strcmp(char *s1, char *s2);
int my_strncmp(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*get_builtin_function(char *name))(char **args, char **args_start);
int exit_shell(char **args, char **args_start);
int environment_shell(char **args, char __attribute__((__unused__)) **args_start);
int set_environment_variable(char **args, char __attribute__((__unused__)) **args_start);
int unset_environment_variable(char **args, char __attribute__((__unused__)) **args_start);
int change_directory(char **args, char __attribute__((__unused__)) **args_start);
int alias_shell_command(char **args, char __attribute__((__unused__)) **args_start);
int display_help(char **args, char __attribute__((__unused__)) **args_start);

/* Builtin Helpers */
char **copy_environment(void);
void free_environment(void);
char **get_environment_variable(const char *name);

/* Error Handling */
int handle_error(char **args, int code);
char *error_environment(char **args);
char *error_message_1(char **args);
char *exit_error_message_2(char **args);
char *cd_error_message_2(char **args);
char *syntax_error_message_2(char **args);
char *error_126_message(char **args);
char *error_127_message(char **args);

/* Linked List Functions */
alias_entry_t *add_alias_end(alias_entry_t **list, char *name, char *value);
void free_alias_list(alias_entry_t *list);
dir_list_t *add_node_end(dir_list_t **list, char *path);
void free_directory_list(dir_list_t *list);

void display_all_help(void);
void display_alias_help(void);
void display_cd_help(void);
void display_exit_help(void);
void display_help_help(void);
void display_environment(void);
void display_set_environment(void);
void display_unset_environment(void);
void display_history(void);

ssize_t get_new_environment(char *buffer);
void perform_logical_operations(char *line, ssize_t *line_length);
void set_alias(char *name, char *value);
void print_aliases(alias_entry_t *list);
int alias_shell_command(char **args, char __attribute__((__unused__)) **args_start);
int process_files_and_commands(char *file_path, int *exit_return);
#endif
