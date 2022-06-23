#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "eServicios.h"
#include "utn.h"

int main(void) {
	setbuf(stdout,NULL);
	int option = 0;
	int cargoServicio= 0;
	LinkedList* listaServicios = ll_newLinkedList();
	LinkedList* listaFiltrada = ll_newLinkedList();

	do{
			utn_getNumero(&option, "\n1. Cargar archivo\n"
			    	    			"2. Imprimir lista\n"
			    	    			"3. Asignar totales\n"
			    	    			"4. Filtrar por tipo\n"
			    	    			"5. Mostrar servicios\n"
			    	    			"6. Guardar servicios\n"
			    	    			"7. Salir\n",
									"\nOpcion invalida\n", 1,7,3);

			switch(option){
				case 1:
					  if(!controller_loadFromText(listaServicios)){
						  printf("\nLista Cargada exitosamente\n");
						  cargoServicio = 1;
					  }else{
						printf("error al cargar lista\n");
					  }
					break;
				case 2:\
					if(cargoServicio == 1){
						if(controller_ListServicios(listaServicios) == -1){
							printf("\nError al imprimir la lista!!\n");
						}
					}else{
						printf("\n Debe cargar los servicios primero!!\n");
					}
					break;
				case 3:
					if(cargoServicio == 1){
						if(!controller_calcularTotal(listaServicios)){
							printf("\n Total calculado correctamente!\n");
						}else{
							printf("\n Error al calcular el total!!\n");
						}
					}else{
						printf("\n Debe cargar los servicios primero!!\n");
					}
					break;
				case 4:
					listaFiltrada= controller_filtrarPorTipo(listaServicios);
					if(listaFiltrada != NULL){
						printf("\n Lista filtrada correctamente");
					}else{
						printf("\n Error al filtrar la lista!!\n");
					}
					break;
				case 5:
					if(!controller_sortServicios(listaServicios)){
						if(controller_ListServicios(listaServicios) == -1){
							printf("\nError al imprimir la lista!!\n");
						}
					}else{
						printf("\n Error al ordenar la lista!");
					}
					break;
				case 6:
					if(!controller_saveAsText("listaOrdenada.csv", listaServicios)){
						printf("\nLista guardada correctamente!\n");
					}else{
						printf("\n Error al guardar la lista!!\n");
					}
					break;
			}
	}while(option != 7);
	return EXIT_SUCCESS;
}
