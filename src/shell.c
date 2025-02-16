#include "shell.h"

Line get_line(char *string) {
    Line line;
    
    char *token = strtok(string, " ");
    strcpy(line.command, token);

    token = strtok(NULL, " ");
    line.nr_args = 0;
    while (token) {
        strcpy(line.args[line.nr_args++], token);
        token = strtok(NULL, " ");
    }

    return line;
}

void cd_handler(Line line) {
    int result;
    if (line.nr_args > 1) {
        printf("bash: cd: too many arguments\n");
        return;
    }

    if (line.nr_args == 0 || strcmp(line.args[0], "~") == 0) {
        chdir(getenv("HOME"));
    } else {
        result = chdir(line.args[0]);
        if (result == -1) {
            printf("bash: cd: %s: No such file or directory\n", line.args[0]);
        }
    }
}

void process_handler(Line line) {
    __pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Couldn't execute command\n");
        exit(-1);
    } else if (pid == 0) { /* Check if child process */
        int result;
        char *args[line.nr_args + 2];
        
        args[0] = line.command;
        for (int i = 1; i <= line.nr_args; ++i) {
            args[i] = line.args[i - 1];
        }
        args[line.nr_args + 1] = NULL;

        result = execvp(line.command, args);
        if (result == -1) {
            perror(NULL);
        }
    } else { /* Parent process */
        wait(NULL);
    }
}

void process_input(char *string) {
    Line line = get_line(string);

    if (strcmp(line.command, "cd") == 0) {
        cd_handler(line);
    } else if (strcmp(line.command, "pwd") == 0) {
        printf("%s\n", getcwd(NULL, 0));
    } else if (strcmp(line.command, "exit") == 0) {
        exit(0);
    } else {
        process_handler(line);
    }
}