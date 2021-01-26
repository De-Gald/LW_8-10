#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(void) {
    pid_t child_pid = -1;

    int n = 0;

    printf("Enter the matrix's size: ");
    scanf("%d", &n);

    int matrix[n][n];

    printf("Enter the matrix's elements\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("The matrix:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    int fd[2];
    pipe(fd);

    child_pid = fork();
    wait(NULL);

//        Parent process
    if (child_pid > 0) {
        close(fd[1]);
        int row_sums[n];
        read(fd[0], row_sums, sizeof(row_sums));
        int column_sum;
        int column_sums[n];
        for (int i = 0; i < n; i++) {
            column_sum = 0;
            for (int j = 0; j < n; j++) {
                column_sum += matrix[j][i];
            }
            column_sums[i] = column_sum;
        }
        int flag = 0;
        for (int j = 0; j < n; j++) {
            if (row_sums[j] == column_sums[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
            printf("There's at least one pair of equal corresponding row and column sums");
        else
            printf("There're no pairs meeting the condition");
    }

//        Child process
    if (child_pid == 0) {
        int row_sum;
        int row_sums[n];
        for (int i = 0; i < n; i++) {
            row_sum = 0;
            for (int j = 0; j < n; j++) {
                row_sum += matrix[i][j];
            }
            row_sums[i] = row_sum;
        }
        close(fd[0]);
        write(fd[1], row_sums, sizeof(row_sums));
        kill(getpid(), SIGTERM);
    }
    return 0;
}

