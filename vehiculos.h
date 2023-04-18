#ifndef VEHICULOS_H
#define VEHICULOS_H

//Definicion de constantes para la estructura 'Vehiculos'
#define TAM_ID_MAT     7
#define TAM_ID_USUARIO  4
#define TAM_NUM_PLAZAS  1
#define TAM_DESC_VEH    50
//Definicion de constantes de vehiculos.txt


//Definicion de estructura vehiculos
typedef struct{
char  *Id_mat;              //7
int   *Id_usuario;          //4
int   *Num_plazas;          //1
char  *Desc_veh;            //50
}Vehiculos;

//Funciones Públicas
void admin_vehiculos(int *, int *, Vehiculos, Usuario);             //Funcion que muestra por pantalla el menu de opciones de administrador, ademas de la ejecucion de las distintos comandos
void usuario_vehiculos(int, Vehiculos, Usuario, int *, int *);      //Funcion que muestra por pantalla el menu de opciones de usuario, ademas de la ejecucion de las distintos comandos
Vehiculos CargarEstructura(int *)                                  //Funcion que copia el contenido de "vehiculos.txt" a cadenas
void *almacena_vehiculos(Vehiculos *, int);                         //Funcion que escribe el contenido de las casdenas en el fichero "vehiculos.txt"



//Prototipos de las funcion vehiculos para menu_usuario
void alta_vehiculos (Vehiculos *, Usuario *, int, int);
void dar_alta (Vehiculos *,int *);
void eliminar_vehiculo (Vehiculos *, Usuario *, int, int, int);
void modificar_vehiculo (Vehiculos *, Usuario *, int, int, int);




#endif  //VEHICULOS_H_INCLUDED
