#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

char line[64];
int array[sizeof line][sizeof line] = {0};

int perform(int line) {
    int result;
    result = (array[line][0] * array[line][1] +
              array[line][2] * array[line][3] +
              array[line][4] / array[line][5] +
              array[line][6] * array[line][7]) / array[line][8] + array[line][9];
    return result;
}

int main(void) {
//    Read file
    FILE *file;
    file = fopen("input.txt", "r");
    int lineNumber = 0;

    if (file == NULL) {
        printf("Reading error\n");
        exit(0);
    }

//    Reading the file by lines
    while (fgets(line, sizeof line, file) != NULL) {
        char *number_str;
        number_str = strtok(line, " ");

//        Check if there're multiple numbers on the line
        int number;
        int count = 0;
        while (number_str != NULL) {
            number = atoi(number_str);
            array[lineNumber][count] = number;
            number_str = strtok(NULL, " ");
            count++;
        }
        lineNumber++;
    }
    fclose(file);

//    Create a different process for each line of the input file
    int index;
    pid_t child_pid;
    int result;

    for (index = 0; index < lineNumber; ++index) {
        child_pid = fork();

//        Child process
        if (child_pid == 0) {
            sleep(1);
            result = perform(index);

            printf("(%d * %d + %d * %d + %d / %d + %d * %d) / %d + %d = %d\n",
                   array[index][0],
                   array[index][1],
                   array[index][2],
                   array[index][3],
                   array[index][4],
                   array[index][5],
                   array[index][6],
                   array[index][7],
                   array[index][8],
                   array[index][9],
                   result);
            exit(0);
        }
    }
    while (wait(NULL) > 0);
    return 0;
}
