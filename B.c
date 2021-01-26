#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int i = 15;
    int fd;
    int B;
    char result[256];

    while (i > 0) {
        fd = open("B >> A", O_WRONLY);
        printf("Enter B: ");
        scanf("%d", &B);
        write(fd, &B, sizeof B);
        close(fd);

        fd = open("B >> A", O_RDONLY);
        read(fd, &result, sizeof result);
        printf("%s\n", result);
        close(fd);

        fd = open("B >> A", O_RDONLY);
        read(fd, &result, sizeof result);
        printf("%s\n", result);
        close(fd);

        i--;
    }

    return 0;
}