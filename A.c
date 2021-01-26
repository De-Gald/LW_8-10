#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>

int main() {
    int A, B, C;
    int fd, fd2;
    int i = 15;

    char positive[32] = "Correct guess";
    char negative[32] = "Wrong guess";
    char positive_B[32] = "B was right";
    char negative_B[32] = "B was wrong";
    char positive_C[32] = "C was right";
    char negative_C[32] = "C was wrong";

    mkfifo("B >> A", S_IFIFO | 0666);
    mkfifo("C >> A", S_IFIFO | 0666);

    while (i > 0) {
        srand(time(NULL));
        A = rand() % 10;
        printf("A = %d\n", A);

        fd = open("B >> A", O_RDONLY);
        read(fd, &B, sizeof B);
        close(fd);

        fd = open("C >> A", O_RDONLY);
        read(fd, &C, sizeof C);
        close(fd);

        fd2 = open("C >> A", O_WRONLY);
        fd = open("B >> A", O_WRONLY);
        if (A == B) {
            write(fd, &positive, sizeof positive);
            write(fd2, &positive_B, sizeof positive_B);
        } else {
            write(fd, &negative, sizeof negative);
            write(fd2, &negative_B, sizeof negative_B);
        }
        close(fd);
        close(fd2);

        fd2 = open("B >> A", O_WRONLY);
        fd = open("C >> A", O_WRONLY);
        if (A == C) {
            write(fd, &positive, sizeof positive);
            write(fd2, &positive_C, sizeof positive_C);
        } else {
            write(fd, &negative, sizeof negative);
            write(fd2, &negative_C, sizeof negative_C);
        }
        close(fd);
        close(fd2);

        i--;
    }
    unlink("B >> A");
    unlink("C >> A");

    return 0;
}