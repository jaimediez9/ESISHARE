#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int opcion;

    do {
        printf("MENU\n");
        printf("1. Publicar viaje\n");
        printf("2. Editar viaje\n");
        printf("3. Incorporarme a viaje\n");
        printf("4. Listar viajes publicados\n");
        printf("5. Salir\n");
        printf("Ingrese la opcion deseada: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                 printf("publicar_viaje()\n");
                break;
            case 2:
                 printf("editar_viaje()\n");
                break;
            case 3:
                printf("incorporarme_a_viaje()\n");
                break;
            case 4:
                 printf("listar_viaje()\n");
                break;
            case 5:
                printf("Salir del programa\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }

    } while(opcion != 5);

    return 0;
}
