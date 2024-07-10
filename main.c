#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 2048
/* functions declarations*/
void read_input(char *);
int parse_input(char **, char *);
void execute_command(char **);

/* functions definitions*/
void
read_input(char *input_buffer) {
    char PWD[MAX_INPUT_LENGTH];
    char *pwd = getcwd(PWD, sizeof(PWD));

    fflush(stdout);
    printf("%s > ", pwd);
    if(fgets(input_buffer, MAX_INPUT_LENGTH, stdin) == NULL){
        perror("ERROR");
        exit(1);
    }

    input_buffer[strcspn(input_buffer, "\n")] = '\0';

}

int
parse_input(char **argv, char *input_buffer){
    char *token = strtok(input_buffer, " ");
    int argc = 0;
    while (token != NULL) {
        argv[argc] = token;
        token = strtok(NULL, " ");
        argc++;
    }

    return argc;

}

void
execute_command(char **argv){
    if(strcmp(argv[0], "exit") == 0)
       exit(EXIT_SUCCESS);

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {

        if (execvp(argv[0], argv) == -1) 
            perror("Execution failed");

        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    char input_buffer[MAX_INPUT_LENGTH];
    char *argv[MAX_INPUT_LENGTH];
    int argc = 0;

    while (1) {
        read_input(input_buffer);
        argc = parse_input(argv, input_buffer);
        // printf("argc = %d\n", argc);
        //
        // for (int i = 0; i < argc; i++) {
        //     printf("argv[%d] = %s\n", i, argv[i]);
        // }

        if (argc > 0) {
            execute_command(argv);
        }

    }
    return EXIT_SUCCESS;
}
