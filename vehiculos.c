#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "usuarios.h"
#include "vehiculos.h"



//CABECERA:
//PRECONDICION:
//POSTCONDICION:
void admin_vehiculos(int *numVehiculos, int *numUsuarios, Vehiculos *vectorVehiculos){
    //Función principal de vehiculos, menú de administrador de vehiculos
    char *cad1, *cad2, *cad3, *cad4, s;
    int sel=0, i=0;
    int men1='n', men2='n';
    setlocale(LC_CTYPE, "Spanish");         //Permite caracteres especiales de España, como la ñ o las tildes

    /*Inicialización de la memoria dinámica*/
    cad1=(char *)malloc(TAM_ID_MAT+1*sizeof(char));
    cad2=(char *)malloc(TAM_ID_USUARIO+1*sizeof(char));
    cad3=(char *)malloc(TAM_NUM_PLAZAS+1*sizeof(char));
    cad4=(char *)malloc(TAM_DESC_VEH+1*sizeof(char));


        do{

            do{
            i=0;
            system("cls");           //Limpia la pantalla

                /*Se muestran 4 opciones:*/

                printf("-Administrador-\n");
                printf("Seleccione que desea hacer:    (para ejecutar la accion, pulse la tecla del numero correspondiente a la operacion que desee)\n");
                printf("(1) - Listar vehículos\n");
                printf("(2) - Dar de alta un vehiculo\n");
                printf("(3) - Dar de baja un vehiculo\n");
                printf("(4) - Modificar un vehiculo\n");
                printf("(5) - Volver al menu principal\n");
                fflush(stdin);
                scanf("%i",&sel);

            }while(sel<1 || sel>5);

            switch(sel){

                case 1: /*Funcion de listado de vehículos, muestra por pantalla los vehículos del sistema*/
                    system("cls");
                    printf("\nVehiculos en el sistema:\n");
                        for(i = 0; i<*numVehiculos; i++){
                        printf("Vehiculo en sistema %d: - |%-*s| - |%-*s| - |%-*s| - |%-*s| Guardado\n",
                            i+1, TAM_ID_MAT, vectorVehiculos[i].Id_mat,
                            TAM_ID_USUARIO, vectorVehiculos[i].Id_usuario,
                            TAM_NUM_PLAZAS, vectorVehiculos[i].Num_plazas,
                            TAM_DESC_VEH, vectorVehiculos[i].Desc_veh);}
                    system("pause");
                    break;

                case 2: /*Función de alta de vehículos, premite crear nuevos vehículos*/
                     vectorVehiculos = (Vehiculos *) realloc(vectorVehiculos, (*numVehiculos+1) * sizeof(Vehiculos));       //Reasignacion de memoria dinamica

                        //Inicialización de nuevos datos de vehículo
                        printf ("Introduce el ID de Usuario para el nuevo vehiculo.\n");
                        fflush (stdin);
                        fgets  (cad2, TAM_ID_USUARIO+1, stdin);

                        printf ("Introduzca la matricula del nuevo vehiculo.\n");
                        fflush (stdin);
                        fgets  (cad1, TAM_ID_MAT+1, stdin);

                        printf ("Introduzca las plazas disponibles en el nuevo vehiculo.\n");
                        fflush (stdin);
                        fgets  (cad3, TAM_NUM_PLAZAS+1, stdin);

                        printf ("Haga una descripcion breve del nuevo vehiculo (MAX: 50).\n");
                        fflush (stdin);
                        fgets  (cad4, TAM_DESC_VEH+1, stdin);

                        //Inicialización de vector dinámico
                        vectorVehiculos[*numVehiculos].Id_mat = cad1;
                        vectorVehiculos[*numVehiculos].Id_usuario = cad2;
                        vectorVehiculos[*numVehiculos].Num_plazas = cad3;
                        vectorVehiculos[*numVehiculos].Desc_veh = cad4;

                        //Creación de vehículo
                        printf("Vehiculo %d: - |%-*s| - |%-*s| - |%-*s| - |%-*s| Guardado\n",
                            *numVehiculos + 1, TAM_ID_MAT, vectorVehiculos[*numVehiculos].Id_mat,
                            TAM_ID_USUARIO, vectorVehiculos[*numVehiculos].Id_usuario,
                            TAM_NUM_PLAZAS, vectorVehiculos[*numVehiculos].Num_plazas,
                            TAM_DESC_VEH, vectorVehiculos[*numVehiculos].Desc_veh);

                        (*numVehiculos)++;
                        system("pause");
                    break;

                case 3: /*Función que da de baja un vehículo*/
                    do{

                        printf("Introduce el número del vehiculo que desea eliminar\n");

                        //Listado de vehículos en sistema
                        for(i = 0; i<*numVehiculos; i++){
                        printf("Vehiculo cargado %d: - |%-*s| - |%-*s| - |%-*s| - |%-*s| \n",
                        i+1, TAM_ID_MAT, vectorVehiculos[i].Id_mat,
                           TAM_ID_USUARIO, vectorVehiculos[i].Id_usuario,
                           TAM_NUM_PLAZAS, vectorVehiculos[i].Num_plazas,
                           TAM_DESC_VEH, vectorVehiculos[i].Desc_veh);
                        }
                        fflush(stdin);
                        scanf("%i", &opcion1);
                        opcion1--;

                        //Seleccion del vehículo a eliminar del fichero
                        printf("Vehiculo %d eliminado: - |%-*s| - |%-*s| - |%-*s| - |%-*s| \n",
                        opcion1+1, TAM_ID_MAT, vectorVehiculos[opcion1].Id_mat,
                           TAM_ID_USUARIO, vectorVehiculos[opcion1].Id_usuario,
                           TAM_NUM_PLAZAS, vectorVehiculos[opcion1].Num_plazas,
                           TAM_DESC_VEH, vectorVehiculos[opcion1].Desc_veh);

                        //Eliminar vehículo
                        for(i = opcion1; i<*numVehiculos; i++){
                            vectorVehiculos[i].Id_mat = vectorVehiculos[i+1].Id_mat;
                            vectorVehiculos[i].Id_usuario = vectorVehiculos[i+1].Id_usuario;
                            vectorVehiculos[i].Num_plazas = vectorVehiculos[i+1].Num_plazas;
                            vectorVehiculos[i].Desc_veh = vectorVehiculos[i+1].Desc_veh;
                        }

                    vectorVehiculos = (Vehiculos *) realloc( vectorVehiculos, (*numVehiculos-1) * sizeof(Vehiculos) );
                    (*numVehiculos)--;

                    printf ("¿Quieres eliminar algun otro vehiculo? Si[s]\n\n");
                    fflush (stdin);
                    scanf("%c",&s);

                    }while(s == 'S' || s == 's');

                    break;

                case 4: /*Funcion que modifica un vehiculo*/
                printf ("¿Que vehiculo quiere modificar?\n");

                    for(i = 0; i<*numVehiculos; i++){
                        printf("Vehiculo %d: - |%-*s| - |%-*s| - |%-*s| - |%-*s| \n",
                            i+1, TAM_ID_MAT, vectorVehiculos[i].Id_mat,
                            TAM_ID_USUARIO, vectorVehiculos[i].Id_usuario,
                            TAM_NUM_PLAZAS, vectorVehiculos[i].Num_plazas,
                            TAM_DESC_VEH, vectorVehiculos[i].Desc_veh);
                        }

                    fflush (stdin);
                    scanf("%i",&i); //Seleccion del vehiculo a modificar
                    i--;

                    do{
                        printf ("¿Qué campo quieres modificar?\n\n");
                        printf("(1) - Descripción de un vehículo.\n");
                        printf("(2) - Matrícula de un vehículo.\n");
                        printf("(3) - Plazas de un vehículo.\n");
                        printf("(4) - Salir.\n");
                        fflush (stdin);
                        scanf("%i",&x);

                        switch(x){

                            case 1:{ //Modificacion de la descripcion del vehiculo
                                printf("1 - Nueva descripción del vehículo.\n");
                                fflush(stdin);
                                fgets(cad4, TAM_DESC_VEH + 1, stdin);
                                vectorVehiculos[i].Desc_veh=cad4;
                               } break;

                            case 2:{ //Modificacion de la matricula del vehiculo
                                printf("Actualización de la matrícula del vehículo.\n");
                                fflush(stdin);
                                fgets(cad2, TAM_ID_MAT + 1, stdin);
                                vectorVehiculos[i].Id_mat=cad2;
                                }break;

                            case 3:{ //Modificacion del numero de plazas del vehiculo
                                printf("Actualización del nº de plazas del vehículo.\n");
                                fflush(stdin);
                                fgets(cad3, TAM_NUM_PLAZAS + 1, stdin);
                                vectorVehiculos[i].Num_plazas=cad3;
                                }break;

                            case 4: //Salir del menu de modificacion
                                break;
                            }
                        }while (x>4 || x<1);
                    break;

                case 5:
                    system ("cls"); //Salir de vehiculos (Limpia pantalla para menu principal)
                    break;
                        }

            }while(sel < 1 || sel > 5);

}

//CABECERA:
//PRECONDICION:
//POSTCONDICION:
void usuario_vehiculos(int n, Vehiculos *vh, Vehiculos *usu, int *num_usuario, int *num_vh){
    //Función principal de vehiculos, menú de vehiculos para usuarios

 char f, h;                         //Variables para opciones de menu
 int x, i;                          //Variables para opciones de menu
 char op1 = 'n', op2 = 'n';         //Pàra elegir si volver a repetir

    system ("cls");                 //Limpiar la pantalla

    fflush (stdin);
    printf ("¿Tiene algun vehiculo registrado? S/N\n"); //Pregunta para entrar en la función y si el usuario no tiene uno, preguntara por registrarlo
    scanf ("%c",&f);
    fflush (stdin);

    if (f == 'S' || f == 's'){
     for (i=0; i < *num_usuario; i++){
       if (strcmp(usu[n].Id_usuario, vh[i].Id_usuario)==0){ //Comprueba si efectivamente tiene algun vehiculo, si no encuentra ninguno, sale
     do{
            while (menu1 == 'n' || menu1 == 'N'){ //Para preguntar si repetir
                system ("cls");
        printf ("Bienvenido usuario %s, ¿Que desea realizar?: \n\n",usu[n].Nomb_usuario); //Menu de Vehiculos

        printf("(1) Ver los vehículos que tiene dado de alta\n");
        printf("(2) Dar de alta un nuevo vehículo\n");
        printf("(3) Eliminar un vehiculo ya en alta\n");
        printf("(4) Modificar vehículo\n");
        printf("(5) Volver al menu principal\n");
        fflush(stdin);
        scanf("%i",&x); fflush (stdin);

        switch(x){ //Elegir opcion del menu anterior
            case 1: alta_vehiculos(vh, usu, n, *num_usuario);break;
            case 2: dar_alta(vh, num_vh); break;
            case 3: eliminar_vehiculo (vh, usu, n, *num_usuario, *num_vh); break;
            case 4: modificar_vehiculo (vh, usu, n, *num_usuario, *num_vh); break;
            case 5: system ("cls"); return;
        }do{
            printf("¿Desea salir? S/N\n"); //Elige si repetir o no el menu anterior
            fflush(stdin);
            scanf("%c", &aux2);
            switch (aux2){
                case 'n': break;
                case 'N': break;
                case 's':
                    aux1 = 's';
                    break;
                case 'S':
                    aux1 = 's';
                    break;
                default:
                    printf("\nOpción no valida, por favor, vuelva a intentarlo\n");       //Si el usuario no introduce una opcion correccta, se ejecutará un bucle hasta que se de una respuesta valida
                    break;
            }
        } while (aux2 != 'n' && aux2 != 'N' && aux2 != 's' && aux2 != 'S');
    }} while (x<0 || x>5);
       }


    else {printf ("Usted no tiene ningun vehiculo registrado, ¿Desea dar alguno de alta? s/n\n");    //Pregunta si quiere dar un vehiculo de alta, en caso de que anteriormente dijera que no tiene
            fflush (stdin);
            scanf ("%c",&h);
            if (h == 'S' || h == 's'){ dar_alta(vh, num_vh); }
            else return;}
            fflush (stdin);

     }}

    system("cls");
}


//CABECERA: alta_vehiculos (Vehiculos *vh, Usuarios *usu, int n, int num_usuario)
//PRECONDICION: Los vectores dinamicos vh y usu tienen que estar inicializados, además, n tiene que contener el usuairo actual que se ha loggeado, y num_usuario tiene que estar inicializado con el numero total de usuarios
//POSTCONDICION: Permite ver todos los vehiculos que hay de alta
 void alta_vehiculos (Vehiculos *vh, Usuarios *usu, int n, int num_usuario){
    int i;
    //Permitira al usuario acceder a la lista de vehiculos que tiene dados de alta

  //La siguiente funcion va comparando el usyario con el vehiculo para mostrar unicamente los vehiculos que posee el usuario loggeado
    for (i=0; i < num_usuario; i++){
        if (strcmp(usu[n].Id_usuario, vh[i].Id_usuario)==0){
            printf("\n\nSu vehiculo tiene las siguientes características");
            printf("\n -Descripción-> %s\n -Num de plazas-> %s \n -Matricula->%s ", vh[i].Desc_veh,vh[i].Num_plazas,vh[i].Id_mat);
            }
    }
    printf("\n");
    system("Pause");
 }


//CABECERA: dar_alta (Vehiculos *vh,int *num_vh)
//PRECONDICION: Los vectores dinamicos vh y usu tienen que estar inicializados
//POSTCONDICION: Permite crear un vehiculo
void dar_alta (Vehiculos *vh,int *num_vh){

    //Función que permite crear vehiculos

 vh = (Vehiculos *) realloc( vh, (*num_vh+1) * sizeof(Vehiculos)); //Ajustamos la memoria dinamica de vehiculos para añadir uno mas


 char *cad1,*cad2,*cad3,*cad4;

 //asignamos memoria dinamica a las cadenas
  cad1=(char *) malloc( TAM_ID_MAT+1*sizeof(char) );
  cad2=(char *) malloc( TAM_ID_USUARIO+1*sizeof(char) );
  cad3=(char *) malloc( TAM_NUM_PLAZAS+1*sizeof(char) );
  cad4=(char *) malloc( TAM_DESC_VEH+1*sizeof(char) );


//TAM_ID_MAT          7
//TAM_ID_USUARIO      4
//TAM_NUM_PLAZAS      1
//TAM_DESC_VEH        50

 printf ("Verifica tu ID de usuario");
 fflush (stdin);
 fgets(cad2, TAM_ID_USUARIO+1, stdin);
 fflush (stdin);

 printf ("Introduzca la matricula del nuevo vehiculo");
 fflush (stdin);
 fgets(cad1, TAM_ID_MAT+1, stdin);


 printf ("¿De cuantas plazas dispone?");
 fflush (stdin);
 fgets(cad3, TAM_NUM_PLAZAS+1, stdin);
 fflush (stdin);


 printf("Describa el vehículo a añadir (MAX:50 caracteres)");
 fflush (stdin);
 fgets(cad4, TAM_DESC_VEH+1, stdin);
 fflush (stdin);


 //Llevamos el valor de las cadenas introducidas anteriormente a las estructuras

 vh[*num_vh].Id_mat = cad1;
 vh[*num_vh].Id_usuario = cad2;
 vh[*num_vh].Num_plazas = cad3;
 vh[*num_vh].Desc_veh = cad4;

  num_vh++;

  system ("Pause");

  //Liberamos las cadenas, para no colapsar la memoria

  free(cad1);
  free(cad2);
  free(cad3);
  free(cad4);

  return;

}


//CABECERA:void eliminar_vehiculo (Vehiculos *vh, Usuarios *usu, int n, int num_usuario, int num_vh)
//PRECONDICION: Los vectores dinamicos vh y usu tienen que estar inicializados, además, n tiene que contener el usuairo actual que se ha loggeado, y num_usuario/num_vh tiene que estar inicializado
//con el numero total de usuarios y vehiculos respectivamente
//POSTCONDICION: Permite eliminar un vehiculo del usuario
void eliminar_vehiculo (Vehiculos *vh, Usuarios *usu, int n, int num_usuario, int num_vh){

    //Esta funcion te permitirra elegir que vehiculo quieres borrar

    char c,f; //Para ver si quiere antes ver lo que tiene o simplemente muestra una lista para eliminar // repetir proceso
    int i; //Para el bucle

    do{
    printf ("¿Desea ver la descripcion de los vehiculos que tiene en alta antes de eliminar? s/n \n\n");
    fflush(stdin);
    scanf ("%c",&c);


    if (c == 's' || c == 'S'){ //Para ver la descripcion de los vehiculos antes de borrar alguno
        alta_vehiculos(vh, usu, n, num_usuario);

        printf ("¿Quieres eliminar algun  vehiculo? s/n \n\n");
       fflush (stdin);
       scanf("%c",&f);}


    else {
        printf ("¿Que vehiculo quiere eliminar?\n");
        //Este bucle for mosttrará los vehiculos del usuario loggeado, pero solo la matricula, para saber de que vehiculo se trata
        for (i=0; i < num_usuario; i++){
        if (strcmp(usu[n].Id_usuario, vh[i].Id_usuario)==0){
            printf("-%i: %s\n",i,vh[i].Id_mat); //Para mostrar la "i" de los vehiculos que tiene
            }}
        //Al saber la id, ya puede elegir cual borrar y se eliminara todo
        fflush (stdin);
        scanf("%i",&i);
        vh[i].Desc_veh = '\0';
        vh[i].Id_mat = '\0';
        vh[i].Id_usuario = '\0';
        vh[i].Num_plazas = '\0';


       printf ("¿Quieres eliminar algun otro vehiculo? s/n \n\n");
       fflush (stdin);
       scanf("%c",&f);}

}while(f == 'S' || f == 's');

return;
}


//CABECERA: void modificar_vehiculo (Vehiculos *vh, Usuarios *usu, int n, int num_usuario, int num_vh){
//PRECONDICION: Los vectores dinamicos vh y usu tienen que estar inicializados, además, n tiene que contener el usuairo actual que se ha loggeado, y num_usuario/num_vh tiene que estar inicializado
//con el numero total de usuarios y vehiculos respectivamente
//POSTCONDICION: Modifica un campo de un elemento del vector de vehiculos
void modificar_vehiculo (Vehiculos *vh, Usuarios *usu, int n, int num_usuario, int num_vh){

    //Esta funcion te permitira elegir un vehiculo y modificar lo que desees dentro de este

    int i,x;
    char cad1[51],cad2[8],cad3[2];
     printf ("¿Que vhiculo quiere modificar?\n");
        for (i=0; i < num_usuario; i++){
        if (strcmp(usu[n].Id_usuario, vh[i].Id_usuario)==0){
            printf("-%i: %s\n",i,vh[i].Id_mat);         //Para mostrar la "i" de los vehiculos que tiene
            }printf("\n");}
        fflush (stdin);

        scanf("%i",&i);
        fflush (stdin);

        do{  //Menu para elegir que modificar
        printf ("¿Que quieres modificar? \n\n");

        printf("(1). Descripcion del vehiculo\n");
        printf("(2). Matricula de un vehiculo\n");
        printf("(3). Plazas de un vehiculo\n");
        scanf("%i",&x); fflush (stdin);
        printf ("Introduzca el cambio: ");
        switch(x){
            case 1: {fgets (cad1,51,stdin); fflush (stdin); vh[i].Desc_veh = cad1;}; break;
            case 2: {fgets (cad2,8,stdin);fflush (stdin); vh[i].Id_mat = cad2;}; break;
            case 3: {fgets (cad3,2,stdin);fflush (stdin); vh[i].Num_plazas = cad3;}; break;
        }} while (x>3 || x<0);
        return;

}



/*Funcion que sobreescribe el fichero con la información actualizada en las cadenas generadas por "carga_vehiculos"*/
void *almacena_vehiculos(Vehiculos *alm, int numt) {
     int num = 0;                       //Variable auxiliar para el bucle while que recorrerá el vector dinámico que hay que almacenar en un fichero correspondiente
     char *cad1, *cad2, *cad3, *cad4;   //Cadenas auxiliares

     setlocale(LC_CTYPE, "Spanish");    //Permite caracteres especiales de España

     printf("\nAlmacena Vehiculos.txt en un fichero de texto\n");

    //Se asigna memoria dinámica suficiente para las cadenas auxiliares
           cad1=(char *) malloc( TAM_ID_MAT+1*sizeof(char) );
           cad2=(char *) malloc( TAM_ID_USUARIO+1*sizeof(char) );
           cad3=(char *) malloc( TAM_NUM_PLAZAS+1*sizeof(char) );
           cad4=(char *) malloc( TAM_DESC_VEH+1*sizeof(char) );

     FILE *fich;
     fich = fopen("Vehiculos.txt", "w+");           //Abre el fichero correspondiente en modo lectura
     if (fich==NULL) exit(1);                       //Si no es posible abrir el fichero se termina la ejecución del programa

     while ( num < numt ) {

//Cada nueva iteración se almacenan los campos del elemento direccionado en las cadenas auxiliares
           cad1 = alm[num].Id_mat;
           cad2 = alm[num].Id_usuario;
           cad3 = alm[num].Num_plazas;
           cad4 = alm[num].Desc_veh;

//Función para imprimir varias cadenas de caracteres en un fichero
           fprintf(fich, "%-*s-%-*s-%-*s-%-*s\n", TAM_ID_MAT, cad1, TAM_ID_USUARIO, cad2, TAM_NUM_PLAZAS, cad3, TAM_DESC_VEH, cad4);

//Imprime por pantalla el elemento almacenado en la iteración correspondient
           printf("Vehiculo almacenado %d: - |%-*s| - |%-*s| - |%-*s| - |%-*s| >>> OK\n", num, TAM_ID_MAT, cad1, TAM_ID_USUARIO, cad2, TAM_NUM_PLAZAS, cad3, TAM_DESC_VEH, cad4);
           (num)++;     //Aumenta el contador del bucle para que apunte al siguiente elemento del vector dinámico
     }

     fclose(fich);      //Función para cerrar el fichero

     printf("Se han almacenado %d registros.\n", num);
     system("PAUSE");

     return 0;
}



/*Funcion que copia los datos del fichero a vector dinamico para poder ser usadas por el sistema*/
Vehiculos *carga_vehiculos(int *num){

    Vehiculos *alm;             //Se declara el vector dinámico que va a devolver la función
    char *cad1, *cad2, *cad3, *cad4;        //Cadenas auxiliares para leer desde el fichero
    *num = 0;                   //Como el vector es dinámico el número de elementos actuales se suponen 0

    setlocale(LC_CTYPE, "Spanish");         //Permite caracteres especiales de España

    printf("\nCarga Vehiculos.txt en vector dinámico \n");

    FILE *fich;                         //Declara la variable que se usará para referirse al fichero en cuestión
    fich = fopen("Vehiculos.txt", "r");
    if (fich == NULL) exit(1);          //Si el fichero no se consigue abrir el programa finaliza su ejecución

    while ( !feof(fich) ) {     //El bucle se repite hasta que llegue al final del fichero

        //Se asigna memoria suficiente para almacenar cada campo leido de cada elemento del fichero en cada cadena auxiliar
        cad1=(char *) malloc( TAM_ID_MAT+1*sizeof(char) );
        cad2=(char *) malloc( TAM_ID_USUARIO+1*sizeof(char) );
        cad3=(char *) malloc( TAM_NUM_PLAZAS+1*sizeof(char) );
        cad4=(char *) malloc( TAM_DESC_VEH+1*sizeof(char) );
        fscanf(fich, "%[^-]-%[^-]-%[^-]-%[^\n]\n", cad1, cad2, cad3, cad4);     //formato para que admite espacios

        if (! *num) alm = (Vehiculos *) malloc( (*num+1) * sizeof(Vehiculos) );     //Asignación de memoria dinámica para cargar un nuevo elemento
        else alm = (Vehiculos *) realloc( alm, (*num+1) * sizeof(Vehiculos) );      //Formato para imprimir cada elemento del vector dinámico por pantalla
            printf("Vehiculo (%d): - |%-*s| - |%-*s| - |%-*s| - |%-*s| \n", *num, TAM_ID_MAT, cad1, TAM_ID_USUARIO, cad2, TAM_NUM_PLAZAS, cad3, TAM_DESC_VEH, cad4);

           //Se carga cada cadena de caracteres leida del fichero en el campo correspondiente del elemento del vector direccionado en cada iteración
           alm[*num].Id_mat = cad1;
           alm[*num].Id_usuario = cad2;
           alm[*num].Num_plazas = cad3;
           alm[*num].Desc_veh = cad4;
           (*num)++;
     }

     fclose(fich);      //Función que cierra el fichero

     printf("Se han cargado %d registros.\n", *num);
     system("PAUSE");

     return alm;        //Devuelve un puntero a un vector dinámico cargado con todos los elementos leidos en el fichero

}
