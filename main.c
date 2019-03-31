#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define bufsize 512

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("error! must be 2 parameters: inputfile outputfile");
        return 1;
    }

    freopen(argv[1], "r", stdin);
    if (errno) {
        printf("input file not found %s", argv[1]);
        return errno;
    }
    freopen(argv[2], "a", stdout);
    if (errno) {
        printf("output file not found %s", argv[2]);
        return errno;
    }

    size_t n;
    char buf[bufsize];

    while ((n=read(STDIN_FILENO, buf, bufsize))>0) {
        if (errno) {
            printf("i/o error");
            return errno;
        }
        write(STDOUT_FILENO, buf, n);
        if (errno) {
            printf("i/o error");
            return errno;
        }
    }

    fclose(stdout);
    return 0;
}