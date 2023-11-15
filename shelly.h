#ifndef _SHELL_H_
#define _SHELL_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

/* Constants */
#define END_OF_FILE -2
#define EXIT -3

/* Global environment */
extern char **environ;
/* Global program name */
extern char *name;
/* Global history counter */
extern int hist;

/* Struct for a linked list node */
typedef struct list_s
{
    char *dir;
    struct list_s *next;
} list_t;

/* Struct for builtin commands */
typedef struct builtin_s
{
    char *name;
    int (*f)(char **argv, char **infront);
} builtin_t;

/* Struct for aliases */
typedef struct alias_s
{
    char *name;
    char *value;
    struct alias_s *next;
} alias_t;

/* Global aliases linked list */
extern alias_t *aliass;

/* Main Helpers */
ssize_t _getline(char **, size_t *, FILE *);
void *_reallocate(void *, unsigned int, unsigned int);
char **_strtok(char *, char *);
char *gets_location(char *);
list_t *gets_path(char *);
int execute(char **, char **);
void frees_list(list_t *);
char *_atoi(int);

/* Input Helpers */
void handles_lin(char **, ssize_t);
void var_replacement(char **, int *);
char *gets_argb(char *, int *);
int calls_argb(char **, char **, int *);
int runs_argb(char **, char **, int *);
int handles_argb(int *);
int checks_argb(char **);
void frees_argb(char **, char **);
char **replaces_aliases(char **);

/* String functions */
int _strlen(const char *);
char *_strcat(char *, const char *);
char *_strncat(char *, const char *, size_t);
char *_strcpy(char *, const char *);
char *_strchr(char *, char);
int _strspn(char *, char *);
int _strcmp(char *, char *);
int _strncmp(const char *, const char *, size_t);

/* Builtins */
int (*builtin_get(char *))(char **, char **);
int exit_shell(char **, char **);
int env_shell(char **, char __attribute__((__unused__)) **);
int setenv_shell(char **, char __attribute__((__unused__)) **);
int unsetenv_shell(char **, char __attribute__((__unused__)) **);
int cd_shell(char **, char __attribute__((__unused__)) **);
int shell_alias(char **, char __attribute__((__unused__)) **);
int help_shell(char **, char __attribute__((__unused__)) **);

/* Builtin Helpers */
char **_copiesenv(void);
void frees_env(void);
char **_getenv(const char *);

/* Error Handling */
int creates_error(char **, int);
char *env_error(char **);
char *error1(char **);
char *exiterror_2(char **);
char *cderror_2(char **);
char *syntaxerror_2(char **);
char *error_126(char **);
char *error_127(char **);

/* Linkedlist.c */
alias_t *add_alias_end(alias_t **, char *, char *);
void frees_alias_list(alias_t *);
list_t *add_node_end(list_t **, char *);
void frees_list(list_t *);

/* Helper Functions */
void all_helps(void);
void alias_helps(void);
void cd_helps(void);
void exit_helps(void);
void help_helps(void);
void _env(void);
void _setenv(void);
void _unsetenv(void);
void _history(void);

ssize_t gets_new_ren(char *);
void ops_logical(char *, ssize_t *);
void sets_alias(char *, char *);
void prints_alias(alias_t *);
int alias_shell(char **, char __attribute__((__unused__)) **);
int proc_files_commands(char *file_path, int *exe_ret);

#endif
