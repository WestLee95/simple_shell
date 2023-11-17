#ifndef _man_h_
#define _man_h_

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

typedef struct info
{
    char **man;
    char *enter;
    char **arggs;
    int state;
    int countter;
    char **environ_var;
    char *p_id;
} man_shell;

typedef struct def_s
{
    char divider;
    struct def_s *next;
} def;

typedef struct dap_s
{
    char *line;
    struct dap_s *next;
} dap;

typedef struct dame_list
{
    int Variable_length;
    char *Vall;
    int Value_length;
    struct dame_list *next;
} dame;

typedef struct builtin_s
{
    char *tag;
    int (*f)(man_shell *shd);
} builtin_t;

char *cdErr_message(man_shell *shd, char *memo, char *o, char *d_s);
char *error_cd(man_shell *shd);
char *cmdNotFound_msg(man_shell *shd);
char *exitIn_get(man_shell *shd);

char *dup_mem(const char *s);
int String_length(const char *s);
int comp_char_strings(char string[], const char *miled);
char *string_split(char string[], const char *miled);
int checkInt_inString(const char *s);

void Rev_String(char *s);

void ChangeDirectory(man_shell *shd);
void ChaneUser_dir(man_shell *shd);
void changeDir_ToPrev(man_shell *shd);
void ChangeDir_home(man_shell *shd);

int Change_Dir(man_shell *shd);

int countChar_rep(char *enter, int u);
int syntaxError(char *enter, int u, char last);
int indexOf_char1(char *enter, int *u);
void Print_error_message(man_shell *shd, char *enter, int u, int bool);
int interm_func(man_shell *shd, char *enter);

int find_command(man_shell *shd);

int leave_shell(man_shell *shd);

int (*builtINFunctions(char *cmd))(man_shell *);

int err_call(man_shell *shd, int ave);

int HELP_ret(man_shell *shd);

void assign_Line(char **lptr, size_t *i, char *cushion, size_t k);
ssize_t get_LIne(char **lptr, size_t *i, FILE *flow);

void sing_line_handler(int signal);
char *READ_LINE(int *dub);

char *del_com(char *in);
void loop_shell(man_shell *dsh);

char *swap_non_printed_char(char *enter, int bool);
void addSep_cdLists(def **hs, dap **hl, char *enter);
void next_com_Line(def **l_s, dap **l_l, man_shell *shd);
int split_com(man_shell *shd, char *enter);
char **split(char *enter);

void help_info_env(void);
void help_setup_env(void);
void help_setdown_env(void);
void gen_help(void);
void exit_help(void);

void help_options(void);
void help_option2(void);
void _help_info(void);

def *add_def_node(def **upper, char sep);
void free_def_list(def **upper);
dap *end_dap_node(dap **upper, char *line);
void free_dap_list(dap **upper);

dame *addVar(dame **init, int lvar, char *Vall, int lval);
void freeVar(dame **init);

void copy_info_s(void *newpointer, const void *pointer, unsigned int size);
void *ptr_realloc(void *pointer, unsigned int old_size, unsigned int new_size);
char **pr_malloc(char **pointer, unsigned int old_size, unsigned int new_size);

int getLength_ofInt(int n);
char *intTo_String(int n);
int stringToInt_conv(char *s);

char *string_concat(char *land, const char *source);
char *dup_string(char *land, char *source);
int con_comp(char *s1, char *s2);
char *loc_char_String(char *s, char c);
int acq_len_String(char *s, char *allow);

void right_variable(dame **h, char *in, man_shell *info);
int checkif(dame **h, char *in, char *st, man_shell *info);
char *replace_i(dame **land, char *enter, char *new_input, int newlength);
char *replace_var(char *enter, man_shell *shd);

char *PGLA(char *tag, char *worth);
void set_env_Var(char *tag, char *value, man_shell *shd);
int comp_envV_names(man_shell *shd);
int del_env_var(man_shell *shd);

int comp_env_names(const char *newenv, const char *tag);
char *get_env_var(const char *tag, char **environ_var);
int print_env_var(man_shell *shd);

int check_directory(char *route, int *m);
char *locate_command(char *cmd, char **environ_var);
int if_executable(man_shell *shd);
int check_user_perm_cmd(char *d, man_shell *shd);
int execute_cmd(man_shell *shd);

char *disp_error_info(man_shell *shd);
char *display_path_error(man_shell *shd);

void free_data_struct(man_shell *shd);
void s_data(man_shell *shd, char **man);


#endif
