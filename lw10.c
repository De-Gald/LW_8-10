#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main() {
    int n = 3;

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

    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANONYMOUS;
    int *shmem = mmap(NULL, 128, protection, visibility, -1, 0);

    pid_t child_pid;

    for (int index = 0; index < n; ++index) {
        child_pid = fork();
        wait(NULL);

//        Child process
        if (child_pid == 0) {
            int column_sum;
            column_sum = 0;
            for (int j = 0; j < n; j++) {
                column_sum += matrix[j][index];
            }
            int column_sums[n];
            for (int i = 0; i < index; i++) {
                column_sums[i] = shmem[i];
            }
            column_sums[index] = column_sum;
            memcpy(shmem, column_sums, sizeof(column_sums));
            kill(getpid(), SIGTERM);
        }
    }
    int el;
    int count = 0;
    int special_numbers_sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            el = matrix[j][i];
            if (el > (shmem[i] - el)) {
                count++;
                special_numbers_sum += el;
            }
        }
    }
    int numbers_mean = special_numbers_sum / count;
    printf("The mean of all 'special' numbers is %d", numbers_mean);

    return 0;
}