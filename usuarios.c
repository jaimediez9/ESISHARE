#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "usuarios.h"
#include "menu.h"

int BuscarUsuario(char *usuario, Usuario *arrayusuarios, int n_usuario);
void BorrarUsuario(Usuario *arrayusuarios, int id_i);

//Cabecera: entero login(E/S Usuario: arrayusuario, E/S entero: id, E/S entero: n_usuarios)
//Precondicion: puntero al array de estrucutura Usuario es valido y tiene contenido, estructura cargada y con contenido, recibe el numero de usuarios registrados, n_usuario debe ser mayor o igual a 1, el usuario debe introducir un usuario y contrasena valida
//Postcondicion: la funcion devuelve los permisos que tiene el usuario y si posicion
int login(Usuario *arrayusuarios, int *id, int *n_usuarios){

    int perm = -1, cont = 0, posicion, control = 0, aux, n_usuarios_aux, i = 0;                          //cont para limitar intentos de inicio de sesion
    char usuario_aux[6], contrasena_aux[9];

    n_usuarios_aux = *n_usuarios;

    while(control != 1){
        printf("Introduce usuario: ");
        scanf("%s", usuario_aux);
        fflush(stdin);
        printf("Introduce contrasena: ");
        scanf("%s", contrasena_aux);
        fflush(stdin);

        posicion = BuscarUsuario(usuario_aux, arrayusuarios, n_usuarios_aux);
        if(posicion != -1){
            if(strcmp(contrasena_aux, arrayusuarios[posicion].Contrasena) == 0){
                printf("\n\nBienvenido a ESI Share %s.", arrayusuarios[posicion].Nomb_usuario);
                *id = posicion;                                                                          //Devuelve el id del usuario ya comprobado
                if(strcmp(arrayusuarios[posicion].Perfil_usuario, "administrador") == 0){
                    perm = 2;
                }
                else perm = 1;
                control = 1;
            }
            else printf("contrasena erronea, intentelo de nuevo.\n");
        }
        else{
            printf("Usuario no encontrado.\n1.- Repetir\n2.- Crear cuenta\n\n");
            scanf("%i", &aux);
            while(aux != 1 && aux != 2){
                printf("Error, opcion incorrecta, intentelo de nuevo: ");
                scanf("%i", &aux);
            }
            if(aux == 2){
                arrayusuarios = CrearUsuario(arrayusuarios, *&n_usuarios, 0);
                perm = 3;
                control = 1;
            }
            else{
                i++;
                if(i == 3){
                    printf("\nIntentos maximo alcanzados, saliendo...");
                    control = 1;
                }
            }
        }
    }

    return perm;

}

//Cabecera: entero BuscarUsuario(E/S cadena: usuario, E/S Usuario: arrayusuario, E entero: n_usuario)
//Precondicion: La variable "usuario" debe ser un puntero a una cadena de caracteres que contenga el nombre de usuario a buscar, la estructura Usuario debe contener datos, n_usuario debe ser mayor o igual a 1
//Postcondicion: devuelve la posicion del usuario a buscar
int BuscarUsuario(char *usuario, Usuario *arrayusuarios, int n_usuario){

    int i, posicion = -1;

    for(i = 0; i < n_usuario; i++){
        if(strcmp(usuario, arrayusuarios[i].Usuario) == 0){
            posicion = i;
        }
    }

    return posicion;

}

//Cabecera: entero BuscarUsuarioID(E/S Usuario: arrayusuario, E entero: n_usuario, E entero: op, E entero: ID)
//Precondicion: La estructura Usuario debe contener datos, n_usuario debe ser mayor o igual a 1
//Postcondicion: devuelve la posicion del usuario a buscar
int BuscarUsuarioID(Usuario *arrayusuario, int n_usuario, int op, int ID){

    int i, id, existe, eliminado, intentos = 0;

    if(op == 1) ListarUsuarios(arrayusuario, n_usuario);
    else id = ID;

    do{
        eliminado = 0;
        existe = 0;
        if(op == 1){
            printf("Introduce la id del usuario: ");
            scanf("%i", &id);
            while(id < 1 || id > n_usuario){
                printf("Error, id incorrecta, el rango de id es 0001 a %04i, vuelva a introducir: ");
                scanf("%i", &id);
            }
        }
        for(i = 0; i < n_usuario && (eliminado == 0 && existe == 0); i++){
            existe = 1;
            if(id == arrayusuario[i].Id_usuario){
                if(arrayusuario[i].Eliminado == 1){
                    eliminado = 1;
                    i = -1;
                    if(op == 1) printf("El usuario con esta id (%04i) esta eliminado.\n");
                }
                else existe = 1;
            }
            else{
                if(i == n_usuario - 1) printf("No se ha encontrado al usuario, vuelva a introducir a la ID.\n");
            }
        }
        intentos++;
    }while((existe == 0 || eliminado == 1) && intentos < 3);

    if(intentos == 3 && existe == 0){
        printf("No se ha encontrado el usuario.\nSaliendo de buscar ID...\n");
        i = -1;
    }

    return i;

}

//Cabecera: Funcion CrearUsuario(E/S Usuario: arrayusuario, E/S entero: n_usuario, E entero: op)
//Precondicion: La estructura de usuario debe estar cargada y con datos, reciba el numero de usuarios registrados, n_usuario debe ser mayor o igual a 1, y reciba el permiso de usuario mediante 'op'
//Postcondicion: Se actualiza la estructura Usuarios con los nuevos datos y incrementado su tamaño, devuelve el numero nuevo de usuarios
Usuario *CrearUsuario(Usuario *arrayusuarios, int *n_usuario, int op){

    Usuario *nuevoarray;

    int control = 0, opcion, permiso = 1, usuarios;
    char usuario[6], contrasena[9], nombre[21], localidad[21];

    *n_usuario += 1;
    usuarios = *n_usuario;
    nuevoarray = (Usuario*)realloc(arrayusuarios, (*n_usuario) * sizeof(Usuario));

    // Formulario registro
    while(control == 0){
        printf("Introduce usuario (maximo 5 caracteres): "); /*Colocar*/fflush(stdin);
        fgets(usuario, 6, stdin);
        EliminarSaltoDeLinea(usuario);
        fflush(stdin);

        while(BuscarUsuario(usuario, arrayusuarios, usuarios-1) != -1){        //Comparar que no exista otro usuario igual
            printf("\nEl usuario introducido ya existe, vuelva a introducir otro (maximo 5 caracteres): ");
            scanf("%s", usuario);
            EliminarSaltoDeLinea(usuario);
            fflush(stdin);
        }

        printf("Introduce contrasena (maximo 8 caracteres): ");
        scanf("%s", contrasena);
        EliminarSaltoDeLinea(contrasena);
        fflush(stdin);
        printf("\nIntroduce nombre y apellido (maximo 20 caracteres): ");
        fgets(nombre, 21, stdin);
        EliminarSaltoDeLinea(nombre);
        fflush(stdin);
        printf("Introduce localidad (maximo 20 caracteres): ");
        fgets(localidad, 21, stdin);
        EliminarSaltoDeLinea(localidad);
        fflush(stdin);
        if(op == 1){
            printf("Permisios del usuario:\n1.- Usuario\n2.- Administrador\n");
            scanf("%i", &permiso);
            while(permiso != 1 && permiso != 2){
                printf("Error, vuelva a introducir: ");
                scanf("%i", &permiso);
            }
        }

        // Validacion datos
        printf("\n¿Son correctos los datos introducidos?");
        if(op == 1){
            if(permiso == 1) printf("Permisos: Usuario\n");
            else printf("Permisos: administrador\n");
        }
        printf("Usuario: %s\ncontrasena: %s\nNombre: %s\nLocalidad: %s\n1.- Si || 2.- No || 3.- Cancelar registro\n", usuario, contrasena, nombre, localidad);
        scanf("%i", &opcion);
        while(opcion < 1 && opcion > 3){
            printf("Error, vuelva a introducir: ");
            scanf("%i", &opcion);
        }

        // Verificacion y guardado de usuario con su nueva id;
        if(opcion == 2) printf("Repita el formulario con los datos correctos.\n");
        else{
            if(opcion == 3){
                *n_usuario -= 1;
                memcpy(nuevoarray, arrayusuarios, *n_usuario);
                control = 1;
            }
            else{
                // Guardar en estructura
                nuevoarray[*n_usuario - 1].Id_usuario = nuevoarray[*n_usuario - 2].Id_usuario + 1;
                nuevoarray[*n_usuario - 1].Eliminado = 0;

                strcpy(nuevoarray[*n_usuario - 1].Usuario, usuario);
                strcpy(nuevoarray[*n_usuario - 1].Contrasena, contrasena);
                strcpy(nuevoarray[*n_usuario - 1].Nomb_usuario, nombre);
                strcpy(nuevoarray[*n_usuario - 1].Localidad, localidad);
                if(permiso == 1) strcpy(nuevoarray[*n_usuario - 1].Perfil_usuario, "usuario");
                else strcpy(nuevoarray[*n_usuario - 1].Perfil_usuario, "administrador");

                control = 1;
            }
        }
    }
    // Cierre
    return nuevoarray;

}

//Cabecera: funcion CargarUsuarios(E/S entero: n_usuarios)
//Precondicion: El archivo "usuarios.txt" debe existir y tener el formato correcto para ser leído por la función
//Postcondicion: devuelve el los datos de la estructura Usuarios y el numero de usuarios
Usuario* CargarUsuarios(int *n_usuarios){

    int n_lineas = 0, i;
    Usuario *usuarios;
    FILE *f;

    f = fopen("usuarios.txt", "r");

    if(f == NULL) printf("\nError al abrir usuarios.txt");

    n_lineas = ContarLineas(f);
    *n_usuarios = n_lineas;
    usuarios = (Usuario*)calloc(n_lineas, sizeof(Usuario));     //Memoria dinamica estrucutura

    rewind(f);

    for(i = 0; i < n_lineas; i++){
        fscanf(f, "%d-", &usuarios[i].Id_usuario);
        fscanf(f, "%[^-]-", usuarios[i].Nomb_usuario);
        fscanf(f, "%[^-]-", usuarios[i].Localidad);
        fscanf(f, "%[^-]-", usuarios[i].Perfil_usuario);
        fscanf(f, "%[^-]-", usuarios[i].Usuario);
        fscanf(f, "%[^\n]\n", usuarios[i].Contrasena);
        usuarios[i].Eliminado = 0;
    }

    fclose(f);
    return usuarios;

}

//Cabecera: funcion MostrarDatos(E/S Usuario: arrayusuarios, E entero: id, E entero: n_usuario, E entero: op)
//Precondicion: La estructura de usuario debe estar cargada y con datos, n_usuario debe ser mayor o igual a 1
//Postcondicion: Si op es igual a 1, busca un usuario en el arreglo y muestra su información básica si lo encuentra, si op es igual a 2, muestra la información completa de un usuario del arreglo identificado por el parámetro id ,s i el usuario buscado
//               no se encuentra en el arreglo, se le pedirá al usuario que lo busque de nuevo o que salga de la función
void MostrarDatos(Usuario *arrayusuarios, int id, int n_usuario, int op){

    int id_aux;
    char usuario_aux[6];

    if(op == 1){
        printf("Introduce el usuario a buscar: ");
        scanf("%s", usuario_aux);
        EliminarSaltoDeLinea(usuario_aux);
        fflush(stdin);
        id_aux = BuscarUsuario(usuario_aux, arrayusuarios, n_usuario);
        while(id_aux != -1 && id_aux != -2){
            printf("Error, usuario no encontrado, vuelva a introducir o introduzca -2 para finalizar: ");
            scanf("%s", usuario_aux);
            fflush(stdin);
            EliminarSaltoDeLinea(usuario_aux);
            id_aux = BuscarUsuario(usuario_aux, arrayusuarios, n_usuario);
        }
        id = id_aux;
    }

    if(id > -1){
        printf("\nUsuario: %s\nNombre: %s\nLocalidad: %s", arrayusuarios[id].Usuario, arrayusuarios[id].Nomb_usuario, arrayusuarios[id].Localidad);
        if(op == 1 || op == 2){
            printf("Id_usuario: %i\nPermisos: %s\nEliminado_temp: %i", arrayusuarios[id].Id_usuario, arrayusuarios[id].Perfil_usuario, arrayusuarios[id].Eliminado);
        }
        puts("\n");
    }
    else printf("\nSaliendo de mostrar datos...");

}

//Cabecera: funcion BorrarMenuUsuario(E/S Usuario: arrayusuarios, E/S entero: n_usuario)
//Precondicion: La estructura de usuario debe estar cargada y con datos, n_usuario debe ser mayor o igual a 1
//Postcondicion: Si el usuario elige la opción 1 del menú, se borra el usuario con ID especificado por el usuario, si existe y no ha sido eliminado previamente, si el usuario elige la opción 2 del menú, se busca el usuario por nombre especificado por el usuario,
//               y si existe y no ha sido eliminado previamente, se borra el usuario.
void BorrarMenuUsuario(Usuario *arrayusuarios, int *n_usuario){

    int opcion, id, control = 0;
    char usuario_aux[6];

    printf("Menu borrar usuario:\n1.- Listar usuarios(Metodo id)\n2.- Introducir usuario(Metodo BuscarUsuario)\nOpcion: ");
    scanf("%i", &opcion);
    while(opcion != 1 && opcion != 2){
        printf("Error, opcion no valida, vuelva a introducir: ");
        scanf("%i", &opcion);
    }

    if(opcion == 1){
        id = BuscarUsuarioID(arrayusuarios, *n_usuario, 1, 0);
        if(id == -1) printf("Error, id no encontrada o ya eliminada.\nSaliendo...");
        else BorrarUsuario(arrayusuarios, id);
    }

    if(opcion == 2){
        printf("Introduce el usuario a buscar: ");
        scanf("%s", usuario_aux);
        fflush(stdin);
        EliminarSaltoDeLinea(usuario_aux);
        id = BuscarUsuario(usuario_aux, arrayusuarios, *n_usuario);
        while(id == -1 && control < 3){
            printf("Error, usuario no encontrado, vuelva a introducir: ");
            scanf("%s", usuario_aux);
            fflush(stdin);
            EliminarSaltoDeLinea(usuario_aux);
            id = BuscarUsuario(usuario_aux, arrayusuarios, *n_usuario);
            if(control == 2) printf("Intentos maximos alcanzado, saliendo...\n");
            control++;
        }
        if(control == 3) printf("Error, usuario no encontrado.\nSaliendo...");
        else{
            if(arrayusuarios[id].Eliminado == 1) printf("Error, usuario no encontrada o ya eliminado.\nSaliendo...");
            else BorrarUsuario(arrayusuarios, id);//arrayusuarios[id].Eliminado = 1;
        }
    }

}

//Cabecera: funcion BorrarUsuario(E/S Usuario: arrayusuario, E entero: id_i)
//Precondicion: La estructura de usuario debe estar cargada y con datos, y id_i es un entero no negativo y menor que el tamaño de usuarios
//Postcondicion: Si el usuario en la posición id_i del arreglo arrayusuarios no está eliminado y se confirma su borrado mediante la entrada de usuario, el campo Eliminado de la estructura Usuario correspondiente se actualiza a 1.
void BorrarUsuario(Usuario *arrayusuarios, int id_i){

    int opcion;/*DEBUG*/ printf("\n- %i -\n", id_i);

    printf("¿Desea borrar el usuario %s? 1.- Si  2.- No\n", arrayusuarios[id_i].Usuario);
    scanf("%i", &opcion);
    while(opcion != 1 && opcion != 2){
        printf("Error, opcion incorrecta, vuelva a introducir: ");
        scanf("%i", &opcion);
    }
    /*DEBUG*/ printf("\nEliminado: %s\n", arrayusuarios[id_i].Nomb_usuario);
    if(opcion == 1){
        arrayusuarios[id_i].Eliminado = 1;
        printf("El usuario %s ha sido eliminado.\nVolviendo al menu...", arrayusuarios[id_i].Nomb_usuario);
    }
    else printf("Eliminado cancelado.\nVolviendo al menu...");

}

//Cabecera: funcion ListarUsuarios(E/S Usuario: arrayusuarios, E entero: n_usuario)
//Precondicion: La estructura de usuario debe estar cargada y con datos, n_usuario debe ser mayor o igual a 1
//Postcondicion: Se muestra en pantalla la lista de usuarios ordenados
void ListarUsuarios(Usuario *arrayusuarios, int n_usuario){

    int i;

    printf("Lista de usuarios (Usuario (ID) - Nombre - Localidad - Permisos):\n\n");
    for(i = 0; i < n_usuario; i++){
        if(arrayusuarios[i].Eliminado == 0){
            printf("%s (%04i) - %s - %s - %s\n", arrayusuarios[i].Usuario, arrayusuarios[i].Id_usuario, arrayusuarios[i].Nomb_usuario, arrayusuarios[i].Localidad, arrayusuarios[i].Perfil_usuario);
        }
    }

    //Añadir pausa

}

//Cabecera: funcion EditarUsuario(E/S Usuario: arrayusuarios, E entero: n_usuario, E entero: op, E/S entero: id_user)
//Precondicion: La estructura de usuario debe estar cargada y con datos, n_usuario debe ser mayor o igual a 1, recibe los permisos que tiene el usuario y su posicion
//Postcondicion: devuelve el usuario editado a la estructura
void EditarUsuario(Usuario *arrayusuarios, int n_usuario, int op, int *id_user){

    int opcion, id, control = 0, opcion2;
    char usuario_aux[6], contrasena_aux[9], localidad_aux[21], nombre_aux[21];

    if(op == 1){
        printf("\n¿Desea buscar al usuario por ID o Usuario?  1.- ID  2.- Usuario\n");
        scanf("%i", &opcion);
        while(opcion != 1 && opcion != 2){
            printf("Error, opcion incorrecta, vuelva a introducir: ");
            scanf("%i", &opcion);
        }

        if(opcion == 1) id = BuscarUsuarioID(arrayusuarios, n_usuario, 1, 0);
        else{
            printf("Introduce el usuario a buscar: ");
            scanf("%s", usuario_aux);
            fflush(stdin);
            EliminarSaltoDeLinea(usuario_aux);
            id = BuscarUsuario(usuario_aux, arrayusuarios, n_usuario);
            while((id != -1 && id != -2) && control < 3){
                printf("Error, usuario no encontrado, vuelva a introducir o introduzca -2 para finalizar: ");
                scanf("%s", usuario_aux);
                fflush(stdin);
                EliminarSaltoDeLinea(usuario_aux);
                id = BuscarUsuario(usuario_aux, arrayusuarios, n_usuario);
                control++;
            }
        }

        if(id == -1){
            printf("Error, busqueda de usuario erronea.\nSaliendo...");
        }
        else{
            MostrarDatos(arrayusuarios, id, n_usuario, op = 2);
            opcion = 0;
            do{
                printf("¿Que desea editar?\n1.-Usuario\n2.-Nombre\n3.-contrasena\n4.-Localidad\n5.-Permiso\n6.-Salir"),
                scanf("%i", &opcion);
                system("cls");
                switch(opcion){
                    case 1:
                        printf("Usuario actual: %s\nNuevo usuario: ", arrayusuarios[id].Usuario);
                        scanf("%s", arrayusuarios[id].Usuario);
                        fflush(stdin);
                        EliminarSaltoDeLinea(arrayusuarios[id].Usuario);
                        break;
                    case 2:
                        printf("Nombre actual: %s\nNuevo nombre: ", arrayusuarios[id].Nomb_usuario);
                        scanf("%s", arrayusuarios[id].Nomb_usuario);
                        fflush(stdin);
                        EliminarSaltoDeLinea(arrayusuarios[id].Nomb_usuario);
                        break;
                    case 3:
                        printf("Introduzca la nueva contrasena: ");
                        scanf("%s", arrayusuarios[id].Contrasena);
                        fflush(stdin);
                        EliminarSaltoDeLinea(arrayusuarios[id].Contrasena);
                        break;
                    case 4:
                        printf("Localidad actua: %s\nNueva localidad: ", arrayusuarios[id].Localidad);
                        scanf("%s", arrayusuarios[id].Localidad);
                        fflush(stdin);
                        EliminarSaltoDeLinea(arrayusuarios[id].Localidad);
                        break;
                    case 5:
                        printf("Permiso para el usuario %s\n1.-Usuario\n2.-Administrador\n", arrayusuarios[id].Usuario);
                        scanf("%i", &opcion2);
                        while(opcion2 != 1 && opcion2 != 2){
                            printf("Error, opcion incorrecta, vuelva a introducir: ");
                            scanf("%i", &opcion2);
                        }
                        if(opcion2 == 1) strcpy(arrayusuarios[id].Perfil_usuario, "usuario");
                        else strcpy(arrayusuarios[id].Perfil_usuario, "administrador");
                        break;
                    default:
                        printf("Error, opcion incorrecta.\n");
                }
            }while(opcion != 6);
        }
    }
    else{
        id = id_user; /*DEBUG*/ printf("\n--..-- %i --..--\n", id);

        do{
            fflush(stdin);
            printf("\nIntroduzca los nuevos datos o si desea mantenerlos introduzcalo de nuveo:\nIntroduzca nuevo nombre: ");
            fgets(nombre_aux, 21, stdin);
            EliminarSaltoDeLinea(nombre_aux);
            fflush(stdin);
            printf("Introduzca nueva localidad: ");
            fgets(localidad_aux, 21, stdin);
            EliminarSaltoDeLinea(localidad_aux);
            fflush(stdin);
            printf("Introduzca nuevo usuario: ");
            scanf("%s", usuario_aux);
            fflush(stdin);
            printf("Introduzca nueva contrasena: ");
            scanf("%s", contrasena_aux);
            fflush(stdin);

            while(control != 2){
                printf("¿Son correctos los datos? (1. Si / 2. No)\nNombre: %s - Localidad: %s\nUsuario: %s - Contrasena: %s\n", nombre_aux, localidad_aux, usuario_aux, contrasena_aux);
                scanf("%i", &control);
                while(control != 1 && control != 2){
                    printf("Error, opcion incorrecta, vuelva a introducir: ");
                    scanf("%i", &control);
                }
                if(control == 1){
                    strcpy(arrayusuarios[id].Nomb_usuario, nombre_aux);
                    strcpy(arrayusuarios[id].Localidad, localidad_aux);
                    strcpy(arrayusuarios[id].Usuario, usuario_aux);
                    strcpy(arrayusuarios[id].Contrasena, contrasena_aux);
                    fflush(stdin);
                    control = 2;
                }
                else{
                    printf("\n¿Desea volver a introducir los datos(1) o salir(2)?\n");
                    scanf("%i", &control);
                    while(control != 1 && control != 2){
                        printf("Error, opcion incorrecta, vuelva a introducir: ");
                        scanf("%i", &control);
                    }
                }
            }
        }while(control == 1);
    }

    printf("Saliendo...");

}

//Cabecera: funcion GuardarEstructura(E/S Usuario: arrayusuarios, E entero: n_usuarios)
//Precondicion: La estructura de usuario debe estar cargada y con datos, n_usuario debe ser mayor o igual a 1
//Postcondicion: Guarda los datos de la estructura en el archivo "usuarios.txt"
void GuardarEstrucutura(Usuario *arrayusuarios, int n_usuarios){

    int i = 0;

    FILE *f;

    f = fopen("usuarios.txt","w");
    if(f == NULL) printf("\nError al abrir usuarios.txt");

    while(i < n_usuarios){
        if(arrayusuarios[i].Eliminado != 1){

            fprintf(f, "%04i", arrayusuarios[i].Id_usuario);
            fputc('-', f);
            fputs(arrayusuarios[i].Nomb_usuario, f);
            fputc('-', f);
            fputs(arrayusuarios[i].Localidad, f);
            fputc('-', f);
            fputs(arrayusuarios[i].Perfil_usuario, f);
            fputc('-', f);
            fputs(arrayusuarios[i].Usuario, f);
            fputc('-', f);
            fputs(arrayusuarios[i].Contrasena, f);

            if(i != n_usuarios-1) fputc('\n', f);
        }
        i++;
    }

    fclose(f);

}

//Cabecera: entero ContarLineas(E/S archivo: f)
//Precondicion: archivo declarado
//Postcondicion: devuelve el numero de lineas, usuarios registrado en el sistema
int ContarLineas(FILE *f){

    int i = 1;
    char c;

    while((c = fgetc(f)) != EOF){
        if(c == '\n') i++;
    }

    rewind(f);

    return i;

}

//Cabecera: funcion EliminarSaltoDeLinea(E/S cadena: cadena)
//Precondicion: recibe una cadena de caracteres valida y no vacia
//Postcondicion: devuelve la cadena sin el salto de linea del final
void EliminarSaltoDeLinea(char *cadena){

	int i = strlen(cadena);

	if(cadena[i-1] == '\n') cadena[i-1] = '\0';
}
