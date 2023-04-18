#include<stdio.h>
#include<stdlib.h>
#include<string.h>



#include "menu.h"
#include "usuarios.h"
#include "vehiculos.h"


void MenuUsuarios(Usuario *arrayusuarios, int id, int *n_usuarios);
void MenuAdmin(Usuario *arrayusuarios, int id, int *n_usuarios);
int INI();
void crear_archivo(const char *nombre_archivo);

//Cabecera: funcion menu()
//Precondicion: Se han creado los archivos vehiculos.txt, viajes.txt y pasos.txt, el archivo usuarios.txt se ha creado y contiene informacion valida, y las estructuras usuarios, vehiculos, viajes y pasos estan cargadas.
//Postcondicion: Se han guardado toda estructura en su respectivo archivo
void menu(){

    int ident = 0, id = -1, n_usuarios, num_Vehiculos, opcion, ini, posicion;

    ini = INI();
    if(ini == 1){
        crear_archivo("vehiculos.txt");
        crear_archivo("viajes.txt");
        crear_archivo("pasos.txt");
    }

    ///////////////////////*CARGA DE ESTRUCTURAS*///////////////////////
    Usuario *arrayusuarios;          //Array de usuarios
    arrayusuarios = CargarUsuarios(&n_usuarios);

    Vehiculos *vectorVehiculos;      //Array de vehiculos
    vectorVehiculos = carga_vehiculos(&num_Vehiculos);

    //Cargar estructura viajes
    //Cargar estructura pasos
    ///////////////////////*CARGA DE ESTRUCTURAS*///////////////////////

    do{

        printf("Bienvenido a ESI - Share.\n\n1.- Inicie sesion.\n2.- Crear cuenta\n3.- Salir\n");
        scanf("%i", &opcion);
        while(opcion < 1 ||opcion > 3){
            printf("\nError, no existe la opcion, vuelva a introducir: ");
            scanf("%i", &opcion);
        }

        puts("");

        switch(opcion){
            case 1:
                ident = login(arrayusuarios, &id, &n_usuarios);

                posicion = BuscarUsuario(char *usuario, Usuario *arrayusuarios, int n_usuario);

                if(ident == 1) MenuUsuarios(arrayusuarios, vectorVehiculos, id, &n_usuarios, &num_Vehiculos, &posicion);
                else{
                    if(ident == 2) MenuAdmin(arrayusuarios, vectorVehiculos, id, &n_usuarios, &num_Vehiculos);
                    else{
                        if(ident == 3) puts("");
                        else puts("Error obtencion identificador de usuario");                     //Error obtencion identificador de usuario
                    }
                }
            break;
            case 2:
                arrayusuarios = CrearUsuario(arrayusuarios, &n_usuarios, 0);
            break;
            case 3:
                printf("\nSaliendo...");
            break;
            default:
                printf("\nError en menu");
            break;
        }
    }while(opcion != 3);

    system("cls");      // Limpieza pantalla


    ///////////////////////*GUARDADO DE ESTRUCTURAS*///////////////////////
    GuardarEstrucutura(arrayusuarios, n_usuarios);
    almacena_vehiculos(vectorVehiculos,num_Vehiculos);
    ///////////////////////*GUARDADO DE ESTRUCTURAS*///////////////////////
}

//Cabecera: funcion MenuUsuarios(E/S Usuario: arrayusuarios, E entero: id, E/S entero: n_usuarios)
//Precondicion: debe estar inicializada y cargada las estructuras, debe recibir la id(posicion) del usuario
//Postcondicion: vuelve al menu principal
void MenuUsuarios(Usuario *arrayusuarios, Vehiculos *vectorVehiculos, int id, int *n_usuarios, int *num_Vehiculos, *posicion){

    int control = 0, opcion = 0, opcion2;
    int *id_user;

    //*id_user = id;

    printf("Bienvenido %s\n\n", arrayusuarios[id].Nomb_usuario);

    while(control == 0){
        printf("Menu:\n1.- Perfil\n2.- Vehiculos\n3.- Viajes\n4.- Salir\n");
        scanf("%i", &opcion);
        while(opcion < 1 || opcion > 4){
            printf("Error, no existe la opcion, vuelva a introducir: ");
            scanf("%i", &opcion);
        }

        switch(opcion){
            case 1:
                printf("\nDatos del perfil:\n");
                MostrarDatos(arrayusuarios, id, n_usuarios, 0);
                printf("�Desea cambiar algun dato? 1.- SI   2.- NO");
                scanf("%i", &opcion2);
                while(opcion2 != 1 && opcion2 != 2){
                    printf("Vuelva a introducir: ");
                    scanf("%i", &opcion2);
                }
                if(opcion2 == 1) EditarUsuario(arrayusuarios, n_usuarios, 0, id);      // Funcion modificar
            break;
            case 2:
                usuario_vehiculos(*posicion,vectorVehiculos,arrayusuarios,n_usuarios,num_Vehiculos);
            break;
            case 3:
                // Menu viajes
            break;
            case 4:
                printf("\nSaliendo...");
                control = 1;
            break;
            default:
                printf("Error en menu usuario, saliendo...");
                control = 1;
            break;
        }
    }

}

//Cabecera: funcion MenuAdmin(E/S Usuario: arrayusuarios, E entero: id, E/S entero: n_usuarios)
//Precondicion: debe estar inicializada y cargada las estructuras, debe recibir la id(posicion) del usuario
//Postcondicion: vuelve al menu principal
void MenuAdmin(Usuario *arrayusuarios, Vehiculos *vectorVehiculos, int id, int *n_usuarios, int *num_Vehiculos){

    int control = 0, opcion;

    printf("\nAdministrador %s\n\n", arrayusuarios[id].Nomb_usuario);

    while(control == 0){
        printf("Menu:\n1.- Usuarios\n2.- Vehiculos\n3.- Viajes\n4.- Salir\n");
        scanf("%i", &opcion);
        while(opcion < 1 || opcion > 4){
            printf("Error, no existe la opcion, vuelva a introducir: ");
            scanf("%i", &opcion);
        }

        switch(opcion){
            case 1:
                do{
                    printf("\nMenu usuarios:\n1.- Crear usuario\n2.- Borrar usuario\n3.- Modificar usuario\n4.- Listar usuario\n5.- Salir\n");
                    scanf("%i", &opcion);
                    while(opcion < 1 || opcion > 5){
                        printf("Error, no existe la opcion, vuelva a introducir: ");
                        scanf("%i", &opcion);
                    }
                    puts("");
                    switch(opcion){
                        case 1:
                            arrayusuarios = CrearUsuario(arrayusuarios, *&n_usuarios, 1);
                        break;
                        case 2:
                            BorrarMenuUsuario(arrayusuarios, *&n_usuarios);
                        break;
                        case 3:
                            EditarUsuario(arrayusuarios, *n_usuarios, 1, id);
                        break;
                        case 4:
                            ListarUsuarios(arrayusuarios, *n_usuarios);
                        break;
                        case 5:
                            printf("Saliendo...\n\n");
                        break;
                        default:
                            printf("Error, no existe la opcion.\n");
                        break;
                    }
                }while(opcion != 5);
            break;
            case 2:
                admin_vehiculos(num_Vehiculos, n_usuarios, vectorVehiculos, arrayusuarios);
            break;
            case 3:
                // Menu viajes
            break;
            case 4:
                printf("Saliendo...");
                control = 1;
            break;
            default:
                printf("Error en menu usuario, saliendo...");
                control = 1;
            break;
        }
    }
}

//Cabecera: entero INI()
//Precondicion:
//Postcondicion: Si el archivo "usuarios.txt" no existe, se crea y se pide al usuario que introduzca la contrase�a del primer administrador, si existe devuelve control 0 para que no se creen los demas archivos
int INI(){

    int control = 0;
    char crontrasena[9];

    FILE *f;

    f = fopen("usuarios.txt","r");
    if(f == NULL){
        control = 1;

        f = fopen("usuarios.txt", "w");

        printf("Iniciando programa, creando archivos...\nIntroduce la contrasena para el primer administrador: ");
        scanf("%s", crontrasena);
        fflush(stdin);

        fputs("0001", f);
        fputc('-', f);
        fputs("ADMINISTRADOR", f);
        fputc('-', f);
        fputs("NINGUNA", f);
        fputc('-', f);
        fputs("administrador", f);
        fputc('-', f);
        fputs("admin", f);
        fputc('-', f);
        fputs(crontrasena, f);

        fclose(f);
    }
    else fclose(f);

    return control;

}

//Cabecera: funcion crear_archivo(E cadena: nombre_archivo)
//Precondicion: debe recibir una cadena de caracteres
//Postcondicion: si el archivo no existe lo crea sin contenido
void crear_archivo(const char *nombre_archivo){

    FILE* f;

    f = fopen(nombre_archivo, "r");
    if (f == NULL) {
        f = fopen(nombre_archivo, "w");
        fclose(f);
        printf("El archivo %s ha sido creado.\n", nombre_archivo);
    }
    else{
        fclose(f);
        printf("El archivo %s ya existe.\n", nombre_archivo);
    }
}

