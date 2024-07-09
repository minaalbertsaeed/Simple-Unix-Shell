#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_LENGTH 1024

void
read_input(char *input_buffer)
{
    char PWD[MAX_INPUT_LENGTH];
    char *pwd = getcwd(PWD, sizeof(PWD));

    printf("%s > ", pwd);
    if(fgets(input_buffer, MAX_INPUT_LENGTH, stdin) == NULL){
        perror("ERROR");
        exit(1);
    }

    input_buffer[strcspn(input_buffer, "\n")] = '\0';

}

int
main() {
    while (1) {
        char input_buffer[MAX_INPUT_LENGTH];
        read_input(input_buffer);

        if(strcmp(input_buffer, "exit") == 0)
           exit(EXIT_SUCCESS);

    }
    return EXIT_SUCCESS;
}
