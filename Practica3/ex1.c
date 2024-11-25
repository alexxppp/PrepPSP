#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main (int argc, char* argv[])
{
    char mensaje[] = "Este es el mensaje.";
    char buffer[10];
    int fd, bytes_leidos;

    fd = open("text.txt", O_WRONLY|O_CREAT);
    if (fd == -1) 
    {
        perror("Error");
        return 1;
    }
    // Escribir mensaje en el fichero
    write(fd, mensaje, strlen(mensaje));
    close(fd);

    // Leer mensaje del fichero
    fd = open("text.txt", O_RDONLY);
    printf("Contenido del fichero:\n");
    do {
        bytes_leidos = read(fd, buffer, 1);
        printf("%c", buffer[0]);
    } while (bytes_leidos > 0);
    
    printf("\n");
    close(fd);

    return 0;
}