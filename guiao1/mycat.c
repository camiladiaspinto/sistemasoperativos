#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
 
int main(){
    //abrir o ficheiro em modo leitura 
    // 1 porque só fica no segundo byte 
    char buffer[1024];
    //copiar para o novo ficheiro, em modo escritra
    int n;
    while (n=read(0,buffer,sizeof(buffer))>0)
        write(1,buffer,n);
     return 0;


}