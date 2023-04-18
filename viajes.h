#ifndef _VIAJES_
#define _VIAJES_


struct viajes{
	int Id_viaje[6]; 
	char Id_mat[7];
	char F_inic;
	char H_inic;
	char H_fin;
	int Plazas_libre[1];
	char Tipo_viaje; "Ida o vuelta"
	char Importe; "ej: 3€"
	char Estado;

};


int tiene_vehiculo_alta(int id_usuario);

void publicar_viaje();
void editar_viaje();
void incorporarme_a_viaje();
void listar_viajes();





#endif 
