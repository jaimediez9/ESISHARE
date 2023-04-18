#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "viajes.h"
#include "vehiculo.h"


// Función para verificar si el usuario tiene algún vehículo dado de alta


int tiene_vehiculo_alta(int id_usuario) {
    FILE *vehiculos;
    struct vehiculo veh;
    int encontrado = 0;

    vehiculos = fopen("vehiculos.txt", "rb");
    if (vehiculos == NULL) {
        printf("Error al abrir el archivo de vehiculos.\n");
        exit(1);
    }

    while (fread(&veh, sizeof(vehiculo), 1, vehiculos) == 1) {
        if (veh.id_usuario == id_usuario) {
            encontrado = 1;
            break;
        }
    }

    fclose(vehiculos);

    return encontrado;
}
