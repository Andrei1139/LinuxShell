#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define clear() system("clear")

#define MAX_LEN 100
#define MAx_NR_ARGS 10

typedef struct {
    char command[MAX_LEN];
    char args[MAx_NR_ARGS][MAX_LEN];
    size_t nr_args;
} Line;

void process_input(char *string);