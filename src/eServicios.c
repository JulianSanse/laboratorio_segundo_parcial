#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "eServicios.h"
#include "utn.h"

static int esNumerica(char* cadena, int limite);
static int esFlotante(char* cadena, int limite);

/**
 *\brief Crea un lugar en memoria para un nuevo eServicio
 *return Retorna el espacio en memoria del nuevo eServicio
 */
eServicio* eServicio_new(){
	return (eServicio*) malloc(sizeof(eServicio));
}
eServicio* eServicio_newParametros(char* idStr,char* descripcionStr,char* tipoStr,char* precioUnitarioStr,char* cantidadStr, char* totalServicioStr){
	eServicio* auxiliarServicio= NULL;
	auxiliarServicio = eServicio_new();
	if(auxiliarServicio!= NULL && idStr != NULL && descripcionStr != NULL && tipoStr != NULL && precioUnitarioStr != NULL && cantidadStr != NULL && totalServicioStr != NULL){
		if(eServicio_setIdTxt(auxiliarServicio, idStr) == -1 ||
		   eServicio_setDescripcion(auxiliarServicio, descripcionStr) == -1 ||
		   eServicio_setTipoTxt(auxiliarServicio, tipoStr) == -1 ||
		   eServicio_setPrecioTxt(auxiliarServicio, precioUnitarioStr) == -1 ||
		   eServicio_setCantidadTxt(auxiliarServicio, cantidadStr) == -1 ||
		   eServicio_setTotalTxt(auxiliarServicio, totalServicioStr) == -1)
		{
			eServicio_delete(auxiliarServicio);
			auxiliarServicio= NULL;
			printf("\nSe devolvio un servicio nulo\n");
		}
	}
	return auxiliarServicio;
}
/**
 * \brief Libera el lugar en la memoria de un eServicio
 * \param this eServicio a eliminar/ liberar memoria
 */
void eServicio_delete(eServicio* this){
	if(this != NULL){
		free(this);
	}
}
/************************************************************************************************************************************************************/

/**
 * \brief imprime el servicio que le pasemos
 * \param this Servicio a imprimir
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_imprimir(eServicio* this){
	int retorno = -1;
	char tipoAux[100];

	if(this != NULL){
		switch(this->tipo){
			case 1:
				strcpy(tipoAux, "MINORISTA");
				break;
			case 2:
				strcpy(tipoAux, "MAYORISTA");
				break;
			case 3:
				strcpy(tipoAux, "EXPORTAR");
				break;
	}

		printf("ID: %d - DESCRIPCION: %s - TIPO: %s - PRECIO UNITARIO: %.2f - CANTIDAD: %d - TOTAL SERVICIO: %.2f\n", this->id, this->descripcion, tipoAux, this->precioUnitario, this->cantidad, this->totalServicio);
		retorno =0;
	}
	return retorno;
}
/*
 * \brief calcula y setea el total de un elento
 * \param this Elemento a calcularlarle y setearle el total
 */
void eServicio_CalcularTotal(void* this){

	if(this != NULL){
		float precioAux;
		int cantidadAux;
		float totalAux;
		if(eServicio_getPrecio(this, &precioAux) == -1 ||
		   eServicio_getCantidad(this, &cantidadAux) == -1){
			printf("Error obteniendo el precio o el servicio");
		}else{
			totalAux = precioAux * cantidadAux;
			eServicio_setTotal(this, totalAux);

		}
	}

}
/*
 * \brief devuelve 1 si el tipo del elemento pasado es minorista
 * \param this elemento a determinar si su tipo es minorista
 * return 1 si es minorista o 0 si no lo es
 */
int eServicio_filtrarMinorista(void* this){
	int retorno = 0;
	int tipoAux;

	if(this!= NULL){
		if(eServicio_getTipo(this, &tipoAux) == -1){
			printf("\nerror al obtener el tipo\n");
		}else{
			if(tipoAux == 1){
				retorno = 1;
			}
		}
	}
	return retorno;
}
/*
 * \brief devuelve 1 si el tipo del elemento pasado es mayorista
 * \param this elemento a determinar si su tipo es mayorista
 * return 1 si es mayorista o 0 si no lo es
 */
int eServicio_filtrarMayorista(void* this){
	int retorno = 0;
	int tipoAux;

	if(this!= NULL){
		if(eServicio_getTipo(this, &tipoAux) == -1){
			printf("\nerror al obtener el tipo\n");
		}else{
			if(tipoAux == 2){
				retorno = 1;
			}
		}
	}
	return retorno;
}
/*
 * \brief devuelve 1 si el tipo del elemento pasado es exportar
 * \param this elemento a determinar si su tipo es exportar
 * return 1 si es exportar o 0 si no lo es
 */
int eServicio_filtrarExportar(void* this){
	int retorno = 0;
	int tipoAux;

	if(this!= NULL){
		if(eServicio_getTipo(this, &tipoAux) == -1){
			printf("\nerror al obtener el tipo\n");
		}else{
			if(tipoAux == 3){
				retorno = 1;
			}
		}
	}
	return retorno;
}
/**
 * \brief Compara la descripcion de dos servicios y devuelve cual es la mayor
 * \param alumno1 Primer servicio a comparar la descripcion
 * \param alumno2 segundo servicio a comparar la descripcion
 * \return el mayor
 */
int eServicio_sortByDescripcion(void* servicio1, void* servicio2){
	int retorno;
	char descripcionServicio1[DESCRIPCION_LEN];
	char descripcionServicio2[DESCRIPCION_LEN];

	if(servicio1 != NULL && servicio2!= NULL){
		eServicio_getDescripcion(servicio1, descripcionServicio1);
		eServicio_getDescripcion(servicio2, descripcionServicio2);

		if(descripcionServicio1 != NULL && descripcionServicio2 != NULL){
			retorno = strcmp(descripcionServicio1, descripcionServicio2);
		}
	}

	return retorno;
}
/*******************************************************************SETTERS AND GETTERS*****************************************************************************************/

/**
 * \brief establece el id en int de un eServicio
 * \param this eServicio a setearle el id
 * \param id Id que le queremos setear
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_setId(eServicio* this,int id){
	int retorno = -1;

	if(this != NULL && id>0 ){
		this->id= id;
		retorno =0;
	}

	return retorno;
}
/**
 * \brief obtiene el id en int de un eServicio
 * \param this eServicio a obtenerle el id en int
 * \param id puntero a la variable donde queremos guardar ese id
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_getId(eServicio* this,int* id){
	int retorno = -1;

	if(this != NULL && id >= 0){
		*id = this->id;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief establece el id en texto de un eServicio
 * \param this eServicio a setearle el id en texto
 * \param id Id que le queremos setear
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_setIdTxt(eServicio* this, char* id){
	int retorno = -1;

	if(this != NULL && id != NULL){
		if(esNumerica(id, 10)){
			retorno = 0;
			this->id = atoi(id);
		}
	}
	return retorno;
}
/**
 * \brief obtiene el id en texto de un eServicio
 * \param this eServicio a obtenerle el id en texto
 * \param id puntero a la variable (De texto) donde queremos guardar ese id
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_getIdTxt(eServicio* this, char* id){
	int retorno = -1;

	if(this != NULL && id != NULL){
		sprintf(id, "%d", this->id);
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief establece el descripcion de un eServicio
 * \param this eServicio a setearle el descripcion
 * \param descripcion descripcion que le queremos setear
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_setDescripcion(eServicio* this,char* descripcion){
	int retorno = -1;

	if(this != NULL && descripcion != NULL){
		strcpy(this->descripcion, descripcion);
		retorno = 0;
	}

	return retorno;
}
/**
 * \brief obtiene el descripcion en texto de un eServicio
 * \param this eServicio a obtenerle el descripcion
 * \param descripcion puntero a la variable (De texto) donde queremos guardar ese descripcion
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_getDescripcion(eServicio* this,char* descripcion){
	int retorno = -1;

	if(this != NULL && descripcion != NULL){
		strcpy(descripcion, this->descripcion);
		retorno = 0;
	}

	return retorno;
}
/**
 * \brief establece el tipo en int de un eServicio
 * \param this eServicio a setearle el tipo
 * \param tipo Tipo que le queremos setear
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_setTipo(eServicio* this,int tipo){
	int retorno = -1;

	if(this != NULL && tipo>0 ){
		this->tipo= tipo;
		retorno =0;
	}

	return retorno;
}
/**
 * \brief obtiene el tipo en int de un eServicio
 * \param this eServicio a obtenerle el tipo en int
 * \param tipo puntero a la variable donde queremos guardar ese tipo
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_getTipo(eServicio* this,int* tipo){
	int retorno = -1;

	if(this != NULL && tipo >= 0){
		*tipo = this->tipo;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief establece el tipo en texto de un eServicio
 * \param this eServicio a setearle el tipo en texto
 * \param tipo Tipo que le queremos setear
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_setTipoTxt(eServicio* this, char* tipo){
	int retorno = -1;

	if(this != NULL && tipo != NULL){
		if(esNumerica(tipo, 10)){
			retorno = 0;
			this->tipo = atoi(tipo);
		}
	}
	return retorno;
}
/**
 * \brief obtiene el tipo en texto de un eServicio
 * \param this eServicio a obtenerle el tipo en texto
 * \param tipo puntero a la variable (De texto) donde queremos guardar ese tipo
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_getTipoTxt(eServicio* this, char* tipo){
	int retorno = -1;

	if(this != NULL && tipo != NULL){
		sprintf(tipo, "%d", this->tipo);
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief establece el precio unitario del servicio
 * \param this Servicio a setearle el  precio
 * \param precio Precio unitario que le queremos setear
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_setPrecio(eServicio* this,float precio){
	int retorno = -1;

	if(this != NULL && precio >= 0){
		this->precioUnitario = precio;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief obtiene el precio unitario en float de un servicio
 * \param this Servicio a obtenerle el precio
 * \param precio puntero a la variable float donde queremos guardar ese precio
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_getPrecio(eServicio* this,float* precio){
	int retorno = -1;

	if(this != NULL && precio >= 0){
		*precio = this->precioUnitario;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief establece el precio unitario en txt de un servicio
 * \param this Servicio a setearle el  precio untiario
 * \param precio Precio en txt que le queremos setear
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_setPrecioTxt(eServicio* this, char* precio){
	int retorno = -1;
	float auxiliarPrecio;
	if(this != NULL && precio != NULL){
		if(esFlotante(precio, 6)){
			auxiliarPrecio= atof(precio);
			if(auxiliarPrecio > 0){
				this->precioUnitario = auxiliarPrecio;
				retorno = 0;
			}
		}
	}
	return retorno;
}
/**
 * \brief obtiene el precio en texto de un servicio
 * \param this Servicio a obtenerle el precio
 * \param precio puntero a la variable texto donde queremos guardar ese precio
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_getPrecioTxt(eServicio* this, char* precio){
	int retorno = -1;

	if(this != NULL && precio != NULL){
		sprintf(precio, "%f", this->precioUnitario);
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief establece la cantidad en int de un eServicio
 * \param this eServicio a setearle la cantidad
 * \param cantidad Cantidad que le queremos setear
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_setCantidad(eServicio* this,int cantidad){
	int retorno = -1;

	if(this != NULL && cantidad>0 ){
		this->cantidad= cantidad;
		retorno =0;
	}

	return retorno;
}
/**
 * \brief obtiene la cantidad en int de un eServicio
 * \param this eServicio a obtenerle la cantidad en int
 * \param tipo puntero a la variable donde queremos guardar esa cantidad
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_getCantidad(eServicio* this,int* cantidad){
	int retorno = -1;

	if(this != NULL && cantidad >= 0){
		*cantidad = this->cantidad;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief establece la cantidad en texto de un eServicio
 * \param this eServicio a setearle la cantidad en texto
 * \param cantidad Cantidad que le queremos setear
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_setCantidadTxt(eServicio* this, char* cantidad){
	int retorno = -1;

	if(this != NULL && cantidad != NULL){
		if(esNumerica(cantidad, 10)){
			retorno = 0;
			this->cantidad = atoi(cantidad);
		}
	}
	return retorno;
}
/**
 * \brief obtiene la cantidad en texto de un eServicio
 * \param this eServicio a obtenerle la cantidad en texto
 * \param cantidad puntero a la variable (De texto) donde queremos guardar esa cantidad
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_getCantidadTxt(eServicio* this, char* cantidad){
	int retorno = -1;

	if(this != NULL && cantidad != NULL){
		sprintf(cantidad, "%d", this->cantidad);
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief establece el total del servicio
 * \param this Servicio a setearle el  total
 * \param total Total que le queremos setear
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_setTotal(eServicio* this,float total){
	int retorno = -1;

	if(this != NULL && total >= 0){
		this->totalServicio = total;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief obtiene el total en float de un servicio
 * \param this Servicio a obtenerle el total
 * \param total puntero a la variable float donde queremos guardar ese total
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_getTotal(eServicio* this,float* total){
	int retorno = -1;

	if(this != NULL && total >= 0){
		*total = this->totalServicio;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief establece el total en txt de un servicio
 * \param this Servicio a setearle el total
 * \param total Total en txt que le queremos setear
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_setTotalTxt(eServicio* this, char* total){
	int retorno = -1;
	float auxiliarPrecio;
	if(this != NULL && total != NULL){
		if(esFlotante(total, 6)){
			auxiliarPrecio= atof(total);
			if(auxiliarPrecio >= 0){
				this->totalServicio = auxiliarPrecio;
				retorno = 0;
			}
		}
	}
	return retorno;
}
/**
 * \brief obtiene el total en texto de un servicio
 * \param this Servicio a obtenerle el total
 * \param total puntero a la variable texto donde queremos guardar ese total
 * return -1 en caso de error y 0 en caso de exito
 */
int eServicio_getTotalTxt(eServicio* this, char* total){
	int retorno = -1;

	if(this != NULL && total != NULL){
		sprintf(total, "%f", this->totalServicio);
		retorno = 0;
	}
	return retorno;
}
/****************************************************************************************************************************************************************/
/**
 * \brief Define si una cadena de texto es numerica
 * \param cadena cadena de texto a analizar
 * \param limite limite de la cadena
 * return -1 en caso de error y 0 en caso de exito
 */
static int esNumerica(char* cadena, int limite){

	int retorno = -1;
	int i;
	if(cadena != NULL && limite > 0){
		retorno = 1;
		for(i=0; i<limite && cadena[i] != '\0'; i++){
			if(i==0 &&  (cadena[i] == '+' || cadena[i] == '-')){
				continue;
			}
			if(cadena[i] > '9' || cadena[i] < '0'){
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/*
 * \brief Define si una cadena de texto es flotante
 * \param cadena cadena de texto a analizar
 * \param limite limite de la cadena
 * return -1 en caso de error y 0 en caso de exito
 */
static int esFlotante(char* cadena, int limite){

	int retorno = -1;
	int i;
	int contadorPuntos =0;

	if(cadena != NULL && limite > 0){
		retorno = 1;
		for(i=0; i<limite && cadena[i] != '\0'; i++){
			if(i==0 &&  (cadena[i] == '+' || cadena[i] == '-')){
				continue;
			}
			if(cadena[i] > '9' || cadena[i] < '0'){
				if(cadena[i] == '.' && contadorPuntos == 0){
					contadorPuntos++;
				}else{
					retorno = 0;
					break;
				}
			}
		}
	}
	return retorno;
}
