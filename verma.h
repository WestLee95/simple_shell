#ifndef verma.h
#define verma.h

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <string.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

typedef struct data
{
    char **verma;
    char *enter;
    char **argz;
    int state;
    int count;
    char **environ_var;
    char *process_identifier;
} verma_shell;

typedef struct def_s
{
    char divide;
    struct def_s *next;
} def;

typedef struct dap_s
{
    char *rule;
    struct dap_s *next;
} dap;

typedef struct dame_list
{
    int Variable_length;
    char *value;
    int Value_length;
    struct dame_list *next;
} dame;

typedef struct builtin_s
{
    char *identity;
    int (*f)(verma_shell *dish);
} builtin_t;

char *thumbup(verma_shell *dish, char *send_message, char *p, char *h_f);
char *msg_error_cd(verma_shell *dish);
char *repetitive_msg(verma_shell *dish);
char *obtain_exit(verma_shell *dish);

char *Moon(const char *s);
int String_findLength(const char *s);
int compile_alpha(char string[], const char *delim);
char *cut_string(char string[], const char *delim);
int examine_if_int(const char *s);

void AssistString(char *s);

void alter_Dir(verma_shell *dish);
void alterDir_usr(verma_shell *dish);
void alterDir_prev(verma_shell *dish);
void alterDir_(verma_shell *dish);

int ALT(verma_shell *dish);

int count_repchar(char *enter, int u);
int syntax_err(char *enter, int u, char last);
int index_char(char *enter, int *u);
void error_send_message(verma_shell *dish, char *enter, int u, int bool);
int case_intfunc(verma_shell *dish, char *enter);

int kano(verma_shell *dish);

int lefshell(verma_shell *dish);

int (*builtINFunctions(char *cmd))(verma_shell *);

int G_ERROR(verma_shell *dish, int eva);

int HELP(verma_shell *dish);

void therule(char **lptr, size_t *i, char *buffer, size_t k);
ssize_t gettherule(char **lptr, size_t *i, FILE *stream);

void sing_rule(int sig);
char *READrule(int *dub);

char *del_COMMENT(char *in);
void shell_loop(verma_shell *dish);



void h_env(void);
void h_env_setup_env(void);
void h_env_setdown_env(void);
void gen_h(void);
void exit_h(void);

void help_opt(void);
void a_help_opt(void);
void _help_(void);

def *add_node(def **top, char sep);
void fee_list(def **top);
dap *end_node(dap **top, char *rule);
void free_list(dap **top);

dame *AddVariable(dame **head, int lvar, char *value, int lval);
void FreeVariable(dame **head);

void copy_s(void *newptr, const void *ptr, unsigned int size);
void *prrealloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **prmalloc(char **ptr, unsigned int old_size, unsigned int new_size);

char *PGLA(char *identity, char *value);
void set_envV(char *identity, char *value, verma_shell *dish);
int compa_env_names(verma_shell *dish);
int del_env(verma_shell *dish);





int getInt_length(int n);
char *int_toString(int n);
int string_toInt(char *s);

char *concat(char *dest, const char *src);
char *concpy(char *dest, char *src);
int concomp(char *s1, char *s2);
char *loc_String(char *s, char c);
int acq_String(char *s, char *accept);



int examine_dir(char *path, int *m);
char *z_cmd(char *cmd, char **environ_var);
int check_f(verma_shell *dish);
int check_for_permission(char *d, verma_shell *dish);
int exec_cmd(verma_shell *dish);






void right_var(dame **h, char *in, verma_shell *data);
int more_money(dame **h, char *in, char *st, verma_shell *data);
char *rep_i(dame **head, char *enter, char *new_enter, int nlen);
char *replace_variable(char *enter, verma_shell *dish);

char *non_printed_char_swap(char *enter, int bool);
void adddivides_and_cdLists(def **hs, dap **hl, char *enter);
void nextInrule(def **l_s, dap **l_l, verma_shell *dish);
int split(verma_shell *dish, char *enter);
char **splityy(char *enter);

int compare_envnames(const char *nenv, const char *identity);
char *obtainenv(const char *identity, char **environ_var);
int print_env(verma_shell *dish);

void h_env(void);
void h_env_setup_env(void);
void h_env_setdown_env(void);
void gen_h(void);
void exit_h(void);
char *info_About_error(verma_shell *dish);
char *info_PathError(verma_shell *dish);

#endif
