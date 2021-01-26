#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int i = 15;
    int fd;
    int C;
    char result[256];

    while (i > 0) {
        fd = open("C >> A", O_WRONLY);
        printf("Enter C: ");
        scanf("%d", &C);
        write(fd, &C, sizeof C);
        close(fd);

        fd = open("C >> A", O_RDONLY);
        read(fd, &result, sizeof result);
        printf("%s\n", result);
        close(fd);

//         fd = open("C >> A", O_RDONLY);
//         read(fd, &result, sizeof result);
//         printf("%s\n", result);
//         close(fd);

        i--;
    }

    return 0;
}
