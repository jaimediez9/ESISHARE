#ifndef USUARIOS_H
#define USUARIOS_H

typedef struct{

    int Id_usuario;
    char Nomb_usuario[21];
    char Localidad[21];
    char Perfil_usuario[14];                //Buscar otra forma
    char Usuario[6];
    char Contrasena[9];
    int Eliminado;                          //Eliminado = 0 (no se elimina) Eliminado = 1 (se elimina), no aparece en el archivo

} Usuario;

//Funciones publicas
Usuario* CargarUsuarios(int *n_usuarios);
int login(Usuario *arrayusuarios, int *id, int *n_usuarios);
int BuscarUsuarioID(Usuario *arrayusuario, int n_usuario, int op, int ID);
Usuario *CrearUsuario(Usuario *arrayusuarios, int *n_usuario, int op);
void MostrarDatos(Usuario *arrayusuarios, int id, int n_usuario, int op);
void BorrarMenuUsuario(Usuario *arrayusuarios, int *n_usuario);
void ListarUsuarios(Usuario *arrayusuarios, int n_usuario);
void EditarUsuario(Usuario *arrayusuarios, int n_usuario, int op, int *id_user);
void GuardarEstrucutura(Usuario *arrayusuarios, int n_usuarios);
int ContarLineas(FILE *f);     // Por si alguien quiere usarla ya que vale para todos los archivos
void EliminarSaltoDeLinea(char *cadena);     // Por si alguien quiere usarla ya que vale para todos los archivos


#endif // USUARIOS_H
