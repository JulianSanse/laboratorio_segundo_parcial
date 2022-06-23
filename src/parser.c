#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "eServicios.h"

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param pFile Archivo desde el cual se van a parsear y leer los datos
 * \param pArrayListPassenger Lista donde se cargaran los datos
 * \return int -1 en caso de error y 0 en caso de exito
 *
 */

int parser_eServicioFromText(FILE* pFile, LinkedList* pArrayListServicios){
	int retorno = -1;
		char auxiliarId[4096];
		char auxiliarDescripcion[4096];
		char auxiliarTipo[4096];
		char auxiliarPrecio[4096];
		char auxiliarCantidad[4096];
		char auxiliarTotal[4096];
		eServicio* aux;

		if(pArrayListServicios != NULL && pFile != NULL){
			fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", auxiliarId, auxiliarDescripcion, auxiliarTipo, auxiliarPrecio, auxiliarCantidad, auxiliarTotal);
			do{
				if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", auxiliarId, auxiliarDescripcion, auxiliarTipo, auxiliarPrecio, auxiliarCantidad, auxiliarTotal) == 6){

					aux = eServicio_newParametros(auxiliarId, auxiliarDescripcion, auxiliarTipo, auxiliarPrecio, auxiliarCantidad, auxiliarTotal);
					if(aux !=NULL){
						ll_add(pArrayListServicios, aux);
						retorno = 0;
					}else{
						printf("Error al agregar el servicio a la lista\n");
					}
				}else{
					printf("error al leer el archivo");
				}
			}while(!feof(pFile));
		}

	    return retorno;
}


