#ifndef BUILTIN_H
#define BUILTIN_H

#include "executor.h"

/*
 * Check whether a command is a shell built-in.
 */
int is_builtin(command_t *cmd);

/*
 * Execute a shell built-in command.
 */
int execute_builtin(command_t *cmd);

#endif
