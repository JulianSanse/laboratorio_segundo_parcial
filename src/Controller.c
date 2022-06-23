#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "eServicios.h"
#include "parser.h"
#include "utn.h"
#include "Controller.h"

int controller_loadFromText(LinkedList* pArrayListServicios){
		int retorno = -1;
		FILE* fp;
		char path[200];
		utn_getString(path, 200, "Que archivo desea cargar?", "Archivo incorrecto", 3);
		fp = fopen(path, "r");

		if(fp!= NULL){
			if(!parser_eServicioFromText(fp, pArrayListServicios)){
				retorno = 0;
			}else{
				printf("Error en el parser");
			}
		}else{
			printf("archivo nulo");
		}


		fclose(fp);
		return retorno;
}

/** \brief Listar servicios
 *
 * \param pArrayListeServicio LinkedList lista donde se encuentran todos los eServicios a imprimir
 * \return int -1 en caso de error y 0 en caso de exito
 *
 */
int controller_ListServicios(LinkedList* pArrayListServicios)
{
	int retorno = -1;
    eServicio* aux;
	int len = ll_len(pArrayListServicios);
	int i;

	printf("______________________________________________________LISTA Servicios__________________________________________\n");
	if(pArrayListServicios != NULL){
		for(i = 0; i<len; i++){
			aux=ll_get(pArrayListServicios, i);
			if(aux!=NULL){
				eServicio_imprimir(aux);
			}
		}
		retorno =0;
	}
	return retorno;

}

int controller_calcularTotal(LinkedList* pArrayListServicios){
	int retorno = -1;

	if(pArrayListServicios != NULL){
		pArrayListServicios = ll_map(pArrayListServicios, eServicio_CalcularTotal);
		retorno = 0;
	}
	return retorno;
}

LinkedList* controller_filtrarPorTipo(LinkedList* pArrayListServicios){
	LinkedList* listaFiltrada;
	if(pArrayListServicios != NULL){
		int respuesta;
		utn_getNumero(&respuesta, "\nPor que tipo de servicio desea filtrar?\n 1.Minorista\n 2.Mayorista\n 3.Exportar\n", "\nTipo invalido!\n", 1, 3, 3);

		switch(respuesta){
			case 1:
				listaFiltrada = ll_filter(pArrayListServicios, eServicio_filtrarMinorista);
				controller_saveAsText("dataFiltradaMinorista.csv", listaFiltrada);
				break;
			case 2:
				listaFiltrada= ll_filter(pArrayListServicios, eServicio_filtrarMayorista);
				controller_saveAsText("dataFiltradaMayorista.csv", listaFiltrada);
				break;
			case 3:
				listaFiltrada= ll_filter(pArrayListServicios, eServicio_filtrarExportar);
				controller_saveAsText("dataFiltradaExportar.csv", listaFiltrada);
				break;
		}
	}

	if(listaFiltrada != NULL){
		return listaFiltrada;
	}else{
		return NULL;
	}
}

/** \brief Guarda los datos de los eServicios en el archivo deseado (modo texto).
 *
 * \param path direccion donde se van a guardar los elementos
 * \param pArrayListeServicio Lista de los elementos a guardar
 * \return int -1 en caso de error y 0 en caso de exito
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListServicio)
{
	int retorno =-1;
	int i;
	FILE* fpArchivo;
	int len;
	eServicio* aux;
	int auxId;
	char auxDescripcion[DESCRIPCION_LEN];
	int auxTipo;
	float auxPrecio;
	int auxCantidad;
	float auxTotal;
	len = ll_len(pArrayListServicio);

	fpArchivo = fopen(path, "w");
			if(fpArchivo!=NULL){
				retorno = 0;
				fprintf(fpArchivo,"id_servicio,descripcion,tipo,precioUnitario,cantidad,totalServio\n");
				for(i=0; i<len; i++){
					aux=ll_get(pArrayListServicio,i);
					if(aux != NULL){
						eServicio_getId(aux, &auxId);
						eServicio_getDescripcion(aux, auxDescripcion);
						eServicio_getTipo(aux, &auxTipo);
						eServicio_getPrecio(aux, &auxPrecio);
						eServicio_getCantidad(aux, &auxCantidad);
						eServicio_getTotal(aux, &auxTotal);

						fprintf(fpArchivo,"%d,%s,%d,%f,%d,%f\n", auxId, auxDescripcion, auxTipo, auxPrecio, auxCantidad, auxTotal);
					}
				}
				fclose(fpArchivo);
			}


		return retorno;
}
/** \brief Ordenar eServicio
 *
 * \param path char*
 * \param pArrayListAlumno lista de los servicios a ordenar
 * \return -1  en caso de error y 0 en caso de exito
 *
 */
int controller_sortServicios(LinkedList* pArrayListServicio){
	int retorno = -1;
	if(pArrayListServicio != NULL){
		ll_sort(pArrayListServicio, eServicio_sortByDescripcion, 1);
		retorno = 0;
	}
	return retorno;
}

