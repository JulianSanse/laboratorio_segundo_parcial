#ifndef CONTROLLER_H_
#define CONTROLLER_H_

int controller_loadFromText(LinkedList* pArrayListServicios);
int controller_ListServicios(LinkedList* pArrayListServicios);
int controller_calcularTotal(LinkedList* pArrayListServicios);
LinkedList* controller_filtrarPorTipo(LinkedList* pArrayListServicios);
int controller_saveAsText(char* path , LinkedList* pArrayListServicio);
int controller_sortServicios(LinkedList* pArrayListServicio);

#endif /* CONTROLLER_H_ */
