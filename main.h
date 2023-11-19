#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <errno.h>

extern char **environ;
#define MAX_COMMANDS 100
#define MAX_ARGS 50
#define MAX_PATH_LENGTH 1024


/* Functions for each mode */
void interractive_mode(void);
void non_interractive_mode(void);

/* Function to print prompt*/
void print_prompt(void);


/* Function to read in command */

/* interractive mode */
char *read_command(void);

/* non_interractive mode */
char *read_input(void);

/* To check for EOF condition */
void my_kill(ssize_t n, char *k);


/* Function to free command*/
void free_command(char *command);

/* Function to parse commands separated by ";"*/
char **parse_commands(char *commands);

/* Function to free the memory allocated for parsed commands*/
void free_commands(char **parsed_commands);


/* Function to free the memory allocated for parsed commands*/
void free_commands(char **parsed_commands);


/* Func to parse a single command into arguments using space separation*/
char **parse_command_arguments(char *command);


/* Function to free the memory allocated for parsed command arguments*/
void free_command_arguments(char **args);


/* Functions to get the full pathname of a command*/

char  *check_command_in_current_path(char *command);
char *_getpath(void);
char *full_path_space(char *path_copy);
char *get_full_pathname(char *command, int count);

/* Function to execute a command*/
int execute_command(char *command, int count);
int exec_child(char *full_path, char **args);
int process_status(int status);


/* Function to print to standard output/file stream*/
int my_fprintf(FILE *stream, const char *format, ...);
int my_snprintf(char *str, size_t size, const char *format, ...);

/* count string length */
size_t my_strlen(const char *str);

/* Function to duplicate string*) */
char *my_strdup(const char *str);


/* Function to compare some number of characters of 2 strings */
int my_strncmp(const char *str1, const char *str2, size_t n);


/* Function to handle path mentioned command */
char *remove_path_prefix(const char *str);


/* Functions for built_ins command */
void exec_env(char **variable);

#endif
