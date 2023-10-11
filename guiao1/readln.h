#define READLN_H

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

ssize_t readln(int fd, char* line, size_t size);