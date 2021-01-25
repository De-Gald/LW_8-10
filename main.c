#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

char line[32];
int array[10][sizeof line] = {0};

int perform() {
    int result;
    result = array[0][0] * array[0][1] +
             array[0][2] * array[0][3] +
             array[0][4] * array[0][5] +
             array[0][6] * array[0][7];
    return result;
}

int main(void) {
//    Read file
    FILE *file;
    file = fopen("/Users/vladislavde-gald/CLionProjects/LW_8/input.txt", "r");

    int lineNumber = 0;

    if (file == NULL) {
        printf("Error Reading File\n");
        exit(0);
    }

//    Reading the file by lines
    while (fgets(line, sizeof line, file) != NULL) {
        char *number_str;
        number_str = strtok(line, " ");

//        Check if there're multiple numbers on the line
        int number;
        int count;
        while (number_str != NULL) {
            number = atoi(number_str);
            array[lineNumber][count] = number;
            number_str = strtok(NULL, " ");
            count++;
        }
        if (number_str == NULL) {
            number = atoi(line);
            array[lineNumber][0] = number;
        }
        lineNumber++;
    }
    fclose(file);

//    Create a different process for each line of the input file
    int index;
    pid_t child_pid = -1;
    int result = 0;

    for (index = 0; index < lineNumber; ++index) {
        int fd[2];
        pipe(fd);

        child_pid = fork();
        wait(NULL);

//        Parent process
        if (child_pid > 0) {
            close(0);
            close(fd[1]);
            int arr[1];
            dup(fd[0]);
            read(fd[0], arr, sizeof(arr));
            result = arr[0];
        }

//        Child process
        if (child_pid == 0) {
            switch (index) {
                case 0:
                    result = perform();
                    printf("ID текущего процесса PID: %i\n", getpid());
                    printf("ID родительского процесса- PPID: %i\n", getppid());
                    printf("%d * %d + ",
                           array[0][0],
                           array[0][1]);
                    printf("%d * %d + %d / %d + %d * %d = %d\n",
                           array[0][2],
                           array[0][3],
                           array[0][4],
                           array[0][5],
                           array[0][6],
                           array[0][7],
                           result);

                    int arr[] = {result};
                    close(1);
                    close(fd[0]);
                    dup(fd[1]);
                    write(1, arr, sizeof(arr));
                    kill(getpid(), SIGTERM);
                    break;
                case 1:
                    printf("ID текущего процесса PID: %i\n", getpid());
                    printf("ID родительского процесса- PPID: %i\n", getppid());
                    printf("%d / %d = ", result, array[1][0]);
                    result = result / array[1][0];
                    printf("%d\n", result);

                    int arr1[] = {result};
                    close(1);
                    close(fd[0]);
                    dup(fd[1]);
                    write(1, arr1, sizeof(arr1));
                    kill(getpid(), SIGTERM);
                    break;
                case 2:
                    printf("ID текущего процесса PID: %i\n", getpid());
                    printf("ID родительского процесса- PPID: %i\n", getppid());
                    printf("%d + %d = ", result, array[2][0]);
                    result = result + array[2][0];
                    printf("%d\n", result);
                    kill(getpid(), SIGTERM);
                    break;
            }
        }
    }

    return 0;
}
