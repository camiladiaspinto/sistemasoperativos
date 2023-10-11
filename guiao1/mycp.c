#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
    char buffer[1024];

    int fdo = open(argv[1], O_RDONLY);
    if (fdo == -1)
        return 1;

    int fdd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fdd == -1) {
        close(fdo); // Feche o arquivo de origem se o arquivo de destino não puder ser aberto
        return 1;
    }

    int n;
    while ((n = read(fdo, buffer, sizeof(buffer))) > 0)
        write(fdd, buffer, n);
    
    close(fdo);
    close(fdd);

    return 0;
}
